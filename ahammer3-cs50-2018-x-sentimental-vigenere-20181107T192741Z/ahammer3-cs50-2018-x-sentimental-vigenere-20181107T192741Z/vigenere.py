# This program shifts a string of letters by a key word from plaintext to ciphertext

# import modules
import cs50
import sys

# Check if valid - a function!


def valid(k):
    for char in k:
        if not char.isalpha():
            return False
    # Removed else statement here - it would return true at the first alpha character and ruin rest of process
    return True


def main():

    # Use valid and len to check arguments
    if len(sys.argv) != 2 or not valid(sys.argv[1]):
        print("Try again - incorrect command line parameters")
        sys.exit(1)

    # Set up k and plaintext, remember variable counter
    k = sys.argv[1]
    plaintext = cs50.get_string("plaintext: ")
    counter = 0

    # Set up ciphertext
    print("ciphertext: ", end="")

    # print actual ciphertext based on parameters
    for char in plaintext:
        if not char.isalpha():
            print(char, end="")
            continue  # like in caesar for non alpha characters

        if char.isupper():
            shifter = 65
        else:
            shifter = 97

        plain = ord(char) - shifter
        kshifter = ord(k[counter % len(k)].upper()) - 65
        cipher = (plain + kshifter) % 26
        counter += 1

        print(chr(cipher + shifter), end="")

    print()

    return 0


if __name__ == "__main__":
    main()

# NOTE: In the future, any programs involving functions like valid would probably be better with a def main() in the program and
# calling the following too: if __name__ == "__main__":\n    main()

# NOTE 2: updated this.