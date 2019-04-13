#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program attempts to crack a password given a hash that is passed in */

// Cracked passwords:
//
// anushree:50xcIMJ0y.RXo => YES
// brian:50mjprEcqC/ts => CA
// bjbrown:50GApilQSG3E2 => UPenn
// lloyd:50n0AAUD.pL8g => lloyd
// malan:50CcfIk1QrPr6 => maybe
// maria:509nVI8B9VfuA => TF
// natmelo:50JIIyhDORqMU => nope
// rob:50JGnXUgaafgc => ROFL
// stelios:51u8F0dkeDSbY => NO
// zamyla:50cI2vYkF0YU2 => LOL

//prototype(s)
bool crack(char *input, char *guess, char *salt);

int main(int argc, string argv[])
{
    //check if the # arguments is 2
    if (argc != 2)
    {
        printf("Try again - incorrect command line parameters \n");
        return 1;
    }

    //set the user input string
    char *input = argv[1];

    //create the salt for the first 2 characters, 3rd value of salt will be '\0' to end it
    char salt[3];
    for (int i = 0; i < 2; i++)
    {
        salt[i] = input[i];
    }
    salt[2] = '\0';

    //create a string representation of all possible characters and its length (26*2)

    /* NOTE: adding a '\0' to this alphabet array would work faster - making only one giant loop to check for passwords
        instead of checking each length individually. This is because the program will check for "end of string \0" as well,
        so we don't have to specify the password length every time. However, I found it useful to omit the '\0' character
        and provide each password length as a separate case, because while it is not as efficient, it makes it easier for me
        to read as a learning program, and also allowed me to print out the "not found" and "working" messages easier, which
        helps because this program takes a long time to run (you don't want the user to think it timed out on them when it didn't)
    */

    //possible improvement: organize these letters by frequency in the english language (i.e. eE beginning of strin, qQxX last)
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int len = 52;

    //let the user know we started (this might take awhile)
    printf("Checking passwords...\n");

    //first we start with passwords of length 1
    char guess1[2];
    for (int a = 0; a < len; a++)
    {
        guess1[0] = alphabet[a];
        guess1[1] = '\0';

        if (crack(input, guess1, salt))
        {
            printf("Password Found: %s\n", guess1);
            return 0;
        }
    }
    printf("Passwords of length 1 not found.\n");

    //move onto passwords with length 2
    char guess2[3];
    for (int a = 0; a < len; a++)
    {
        for (int b = 0; b < len; b++)
        {
            guess2[0] = alphabet[b];
            guess2[1] = alphabet[a];
            guess2[2] = '\0';

            if (crack(input, guess2, salt))
            {
                printf("Password Found: %s\n", guess2);
                return 0;
            }
        }
    }
    printf("Passwords of length 2 not found.\n");

    //move onto passwords with length 3
    char guess3[4];
    for (int a = 0; a < len; a++)
    {
        for (int b = 0; b < len; b++)
        {
            for (int c = 0; c < len; c++)
            {
                guess3[0] = alphabet[c];
                guess3[1] = alphabet[b];
                guess3[2] = alphabet[a];
                guess3[3] = '\0';

                if (crack(input, guess3, salt))
                {
                    printf("Password Found: %s\n", guess3);
                    return 0;
                }
            }
        }
    }
    printf("Passwords of length 3 not found.\n");

    //move onto passwords with length 4
    char guess4[5];
    for (int a = 0; a < len; a++)
    {
        for (int b = 0; b < len; b++)
        {
            for (int c = 0; c < len; c++)
            {
                for (int d = 0; d < len; d++)
                {
                    guess4[0] = alphabet[d];
                    guess4[1] = alphabet[c];
                    guess4[2] = alphabet[b];
                    guess4[3] = alphabet[a];
                    guess4[4] = '\0';

                    if (crack(input, guess4, salt))
                    {
                        printf("Password Found: %s\n", guess4);
                        return 0;
                    }
                }
            }
        }
    }
    printf("Passwords of length 4 not found.\n");

    //final atttempt and this will take a very long time: passwords of length 5
    char guess5[6];
    for (int a = 0; a < len; a++)
    {
        //let the user know it is still running here
        printf("working...\n");
        for (int b = 0; b < len; b++)
        {
            for (int c = 0; c < len; c++)
            {
                for (int d = 0; d < len; d++)
                {
                    for (int e = 0; e < len; e++)
                    {
                        guess5[0] = alphabet[e];
                        guess5[1] = alphabet[d];
                        guess5[2] = alphabet[c];
                        guess5[3] = alphabet[b];
                        guess5[4] = alphabet[a];
                        guess5[5] = '\0';

                        if (crack(input, guess5, salt))
                        {
                            printf("Password Found: %s\n", guess5);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("Passwords of length 5 not found.\n");

    printf("Password not found, sorry :(\n");

    return 0;
}

//create a function for crack that compares the output to hash
bool crack(char *input, char *guess, char *salt)
{
    char *encryption = crypt(guess, salt);

    //strcmp checks the two strings, will return 0 if they match (true)
    if (strcmp(encryption, input) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}