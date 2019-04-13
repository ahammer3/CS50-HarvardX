#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program shifts a string of letters by a key word from plaintext to ciphertext */

int main(int argc, string argv[])
{
    //check if the # arguments is 2
    if (argc != 2)
    {
        printf("Try again - incorrect command line parameters \n");
        return 1;
    }

    //get key from command line argument, check for isalpha, initiate counter and kshifter afterwards
    //counter starts at -1 to shift to 0 at start
    string k = argv[1];
    int lenK = strlen(k);

    for (int i = 0; i < lenK; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Try again - incorrect command line parameters \n");
            return 1;
        }
    }
    int counter = -1;
    int kshifter;

    //prompt user for plaintext
    printf("plaintext: ");
    string plaintext = get_string();

    //for each character in plaintext
    //if alphabetic, preserve case, shift by key and print ciphertext
    //else we print the character and do not shift by the key, and move on
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            counter = (counter + 1) % lenK;
            if (isupper(k[counter]))
            {
                kshifter = 65;
            }
            else
            {
                kshifter = 97;
            }

            if (isupper(plaintext[i]))
            {
                int shifter = 65;
                printf("%c", (((plaintext[i] + (k[counter] - kshifter)) - shifter) % 26) + shifter);
            }
            else if (islower(plaintext[i]))
            {
                int shifter = 97;
                printf("%c", (((plaintext[i] + (k[counter] - kshifter)) - shifter) % 26) + shifter);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    return 0;
}