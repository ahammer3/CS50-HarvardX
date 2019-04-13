# This program determines what category an entered CC number is in

# import modules
import cs50
import math

# save variables to see better and get number
d1 = 0
d2 = 0
digits = 0
odds = 0
evens = 0
number = cs50.get_int("Credit Card Number: ")

# start the while loop while number > 0
while number > 0:
    d2 = d1
    d1 = number % 10

    # get the evens and odds
    if digits % 2 == 0:
        evens += d1
    else:
        multiple = 2 * d1
        odds += (multiple // 10) + (multiple % 10)

    # get the count of digits
    number //= 10
    digits += 1

    # make sure number is valid with bool and get first two digits
    valid = (evens + odds) % 10 == 0
    first_two = (d1 * 10) + d2

# print card based on criteria else invalid
if d1 == 4 and digits >= 13 and digits <= 16 and valid:
    print("VISA\n")
elif first_two >= 51 and first_two <= 55 and digits == 16 and valid:
    print("MASTERCARD\n")
elif (first_two == 34 or first_two == 37) and digits == 15 and valid:
    print("AMEX\n")
else:
    print("INVALID\n")