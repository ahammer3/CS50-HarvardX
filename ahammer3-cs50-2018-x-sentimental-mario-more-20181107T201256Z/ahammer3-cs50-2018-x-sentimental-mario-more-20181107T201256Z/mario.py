#  This program displays 2 triangle blocks made of #s

# import module
import cs50

# This loop runs at least once, and continues until input is right
while True:
    height = cs50.get_int("Height: ")
    width = height + 1
    if height >= 0 and height <= 23:
        break

# prints the pyramid per the parameters - this time mirrored to get 2 pyramids
for i in range(1, height + 1):
    hashes = i
    spaces = width - hashes

    print(" " * (spaces - 1), end="")
    print("#" * hashes, end="")

    print("  ", end="")

    print("#" * hashes)