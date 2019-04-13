#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program shifts a string of letters by k letters from plaintext to ciphertext */

int main(int argc, string argv[])
{
    //check if the # arguments is 2
    if (argc != 2)
    {
        printf("Try again - incorrect command line parameters");
        return 1;
    }

    //get key from command line argument, turn into integer
    int k = atoi(argv[1]);

    //prompt user for plaintext
    printf("plaintext: ");
    string plaintext = get_string();

    //for each character in plaintext
    //if alphabetic, preserve case, shift by key and print ciphertext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int shifter = 65;
                printf("%c", (((plaintext[i] + k) - shifter) % 26) + shifter);
            }
            else if (islower(plaintext[i]))
            {
                int shifter = 97;
                printf("%c", (((plaintext[i] + k) - shifter) % 26) + shifter);
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