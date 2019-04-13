# This program outputs the minimum # coins required to make the change given

# import modules
import cs50
import math

# get the change owed in a loop that runs at least once
while True:
    dollars = cs50.get_float("Change owed in dollars: ")
    cents = math.floor(dollars * 100)

    if cents > 0:
        break

# calculate each type of coin using mods
quarters = cents // 25
dimes = (cents % 25) // 10
nickels = ((cents % 25) % 10) // 5
pennies = ((cents % 25) % 10) % 5

# simply print it out!
print(f"{quarters + dimes + nickels + pennies}")