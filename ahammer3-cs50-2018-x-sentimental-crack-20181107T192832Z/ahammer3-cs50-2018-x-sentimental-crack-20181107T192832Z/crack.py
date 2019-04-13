# This program attempts to crack a password given a hash that is passed in
# NOTE: this was so much easier than the C version...

# Cracked passwords:
#
# anushree:50xcIMJ0y.RXo => YES
# brian:50mjprEcqC/ts => CA
# bjbrown:50GApilQSG3E2 => UPenn
# lloyd:50n0AAUD.pL8g => lloyd
# malan:50CcfIk1QrPr6 => maybe
# maria:509nVI8B9VfuA => TF
# natmelo:50JIIyhDORqMU => nope
# rob:50JGnXUgaafgc => ROFL
# stelios:51u8F0dkeDSbY => NO
# zamyla:50cI2vYkF0YU2 => LOL

# import modules
import sys
import crypt  # from cs50 libraries

# Check if the # arguments is 2
if len(sys.argv) != 2:
    print("Try again - incorrect command line parameters")
    sys.exit(1)

# set the user input string
hash = sys.argv[1]

# set the salt using the input
salt = hash[0:2]

# create a string representation of all possible characters - for more notes see the crack.c version
alphabet = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"  # add the space in beginning to account for diff length pass

# start looping - this time we can do all lengths at once
for fifth in alphabet:
    for fourth in alphabet:
        for third in alphabet:
            for second in alphabet:
                for first in alphabet[1:]:  # following with note above, this accounts for pass of at least length 1
                    # generate a guess
                    guess = f"{first}{second}{third}{fourth}{fifth}".strip()

                    # compare the guess
                    if crypt.crypt(guess, salt) == hash:
                        print(guess)
                        sys.exit(0)

# else not found
print("Password not found, sorry :(")

# NOTE: it seems that passwords of length 5 take forever - maybe even longer than c version. Could be an issue to fix, could be
# the nature of brute force.