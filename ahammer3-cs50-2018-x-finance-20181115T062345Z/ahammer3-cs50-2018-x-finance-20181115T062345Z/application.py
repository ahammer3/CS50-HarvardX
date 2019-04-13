import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for  # added url_for import
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Change code here
    # look up the current user + their stocks
    users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares, quote_price FROM transactions WHERE user_id = :user_id and symbol not null GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])

    # prepare quotes and a running total
    quotes = {}
    count = 0
    total = 0

    # implement the quotes and running total
    for stock in stocks:
        quotes[stock["symbol"]] = lookup(stock["symbol"])
        total += stocks[count]["total_shares"] * stocks[count]["quote_price"]
        count += 1

    # get the cash remaining and adjust total
    cash_remaining = users[0]["cash"]
    total += cash_remaining

    # render this template as the "default" page
    return render_template("index.html", quotes=quotes, stocks=stocks, total=total, cash_remaining=cash_remaining)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # Change code here
    # check post
    if request.method == "POST":

        # get a quote
        quote = lookup(request.form.get("symbol"))

        # attempt to convert to int, else apology
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Invalid share amount.")

        # check if valid
        if not quote:
            return apology("Invalid symbol.")

        # check if number positive and valid
        if shares <= 0 or not shares:
            return apology("Invalid share amount.")

        # query database for cash
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # check if there is enough
        if not cash or float(cash[0]["cash"]) < quote["price"] * shares:
            return apology("Insufficient funds.")

        # Updates to the database
        db.execute("UPDATE users SET cash = cash - :price WHERE id = :user_id",
                   price=quote["price"]*shares, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, quote_price, type) VALUES(:user_id, :symbol, :shares, :price, 'BUY')",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=shares,
                   price=quote["price"])

        # message and redirect
        flash("Success!")
        return redirect(url_for("index"))

    # else return the default buy.html
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Change code here
    # There is no post - simply show the history in a table
    history = db.execute(
        "SELECT transaction_id, symbol, shares, quote_price, type, created FROM transactions WHERE user_id = :user_id ORDER BY created", user_id=session["user_id"])

    # adjust rows for add funds (for every time we add funds we count it as 1 share in the history)
    for row in history:
        if row["shares"] == 0:
            row["shares"] = 1

    return render_template("history.html", transactions=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Change code here
    # check post
    if request.method == "POST":

        # get the stock symbol
        quote = lookup(request.form.get("symbol"))

        # check if valid
        if not quote:
            return apology("Invalid symbol.")

        # return quoted
        return render_template("quoted.html", quote=quote)

    # else return the default quote.html
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Change code here
    # check post
    if request.method == "POST":

        # username exists?
        if not request.form.get("username"):
            return apology("Provide username please.")

        # password exists?
        if not request.form.get("password"):
            return apology("Provide password please.")

        # check confirmation
        if not request.form.get("confirmation") == request.form.get("password"):
            return apology("Password confirmation invalid.")

        # hash the password
        hash = generate_password_hash(request.form.get("password"))

        # new user insert
        new_user = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                              username=request.form.get("username"),
                              hash=hash)

        # check the primary key (username)
        if not new_user:
            return apology("Username is taken.")

        # remember this user
        session["user_id"] = new_user

        # message and redirect
        flash("Registration successful!")
        return redirect(url_for("index"))

    # else return the default register.html
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Change code here - similar to buy method
    # first query the stocks for html
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"])

    # check post
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))

        # check if valid
        if not quote:
            return apology("Invalid symbol.")

        # check if positive number valid
        if shares <= 0:
            return apology(f"Can't sell {0} shares!", shares)

        # query database for cash
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # if we made it this far, we can re-assign the stocks query to be more useful
        stocks = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
            user_id=session["user_id"], symbol=request.form.get("symbol"))

        # check if there is enough shares (or valid shares)
        if len(stocks) != 1 or stocks[0]["total_shares"] <= 0 or stocks[0]["total_shares"] < shares:
            return apology("Not enough shares to sell, sorry.")

        # Updates to the database
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id",
                   price=quote["price"]*shares, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, quote_price, type) VALUES(:user_id, :symbol, :shares, :price, 'SELL')",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol"),
                   shares=shares*(-1),
                   price=quote["price"])

        # message and redirect
        flash("Success!")
        return redirect(url_for("index"))

    # else return the default buy.html
    return render_template("sell.html", stocks=stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """User is trying to change password"""

    # check post
    if request.method == "POST":

        # check db for hash
        old = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # check entry of old password
        if len(old) != 1 or not check_password_hash(old[0]["hash"], request.form.get("old_password")):
            return apology("Invalid password entered.")

        # check new password entry - same as register method here
        # password exists?
        if not request.form.get("new_password"):
            return apology("Provide password please.")

        # check confirmation
        if not request.form.get("new_confirmation") == request.form.get("new_password"):
            return apology("Password confirmation invalid.")

        # hash the password
        hash = generate_password_hash(request.form.get("new_password"))

        # update user
        user = db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", user_id=session["user_id"], hash=hash)

        # message and redirect
        flash("Success!")
        return redirect(url_for("index"))

    # else return the default change_password.html
    return render_template("change_password.html")


@app.route("/supplement", methods=["GET", "POST"])
@login_required
def supplement():
    """User is trying to add funds"""

    # check post
    if request.method == "POST":

        # get the amount
        add = float(request.form.get("amount"))

        # check if valid
        if not add or add <= 0 or add > 1000:
            return apology("Invalid amount entered.")

        # update user cash
        db.execute("UPDATE users SET cash = cash + :add WHERE id = :user_id", user_id=session["user_id"], add=add)

        # update transactions
        db.execute("INSERT INTO transactions (user_id, quote_price, type) VALUES(:user_id, :price, 'ADD')",
                   user_id=session["user_id"],
                   price=add)

        # message and redirect
        flash("Success!")
        return redirect(url_for("index"))

    # else return the default supplement.html
    return render_template("supplement.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
