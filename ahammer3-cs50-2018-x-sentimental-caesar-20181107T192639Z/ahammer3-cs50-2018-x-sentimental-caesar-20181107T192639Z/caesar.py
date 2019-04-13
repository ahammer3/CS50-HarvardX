# This program shifts a string of letters by k letters from plaintext to ciphertext

#import modules
import cs50
import sys  # new module sys for python for argv

# account for errors - check if # arguments is 2
if len(sys.argv) != 2:
    print("Try again - incorrect command line parameters")
    sys.exit(1)

# prompt the plaintext and get k from argv
k = int(sys.argv[1])
plaintext = cs50.get_string("Plaintext: ")

# Print the first part of ciphertext
print("ciphertext: ", end="")

# Print the actual ciphertext based on parameters
for char in plaintext:
    if not char.isalpha():
        print(char, end="")
        continue  # Use continue to avoid errors involving non alpha characters

    if char.isupper():
        shifter = 65
    else:
        shifter = 97

    plain = ord(char) - shifter
    cipher = (plain + k) % 26

    print(chr(cipher + shifter), end="")

# Extra endline for aesthetic
print()