# This program displays a triangle block made of #s

# import module
import cs50

# This loop runs at least once, and continues until input is right
while True:
    height = cs50.get_int("Height: ")
    width = height + 1
    if height >= 0 and height <= 23:
        break

# prints the pyramid per the parameters
for i in range(1, height + 1):
    hashes = i + 1
    spaces = width - hashes

    print(" " * spaces, end="")
    print("#" * hashes)