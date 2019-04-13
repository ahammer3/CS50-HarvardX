#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Declare and initialize a variable and ask for user input.
    long long number = 0;

    // Ask for credit card number
    do
    {
        printf("Credit Card Number:");
        number = get_long_long();
    }
    while (number < 0);

    // Determine whether it has a valid number of digitscd ~/workspace/pset1/hello
    int count = 0;
    long long digits = number;
    while (digits > 0)
    {
        digits = digits / 10;
        count++;
    }
    if ((count != 13) && (count != 15) && (count != 16))
    {
        printf("INVALID\n");
    }

    //declare a new array number
    int numberarray[count];

    //adjust card number for index i
    for (int i = 0; i < count; i++)
    {
        numberarray[i] = number % 10;
        number = number / 10; //convert to digits
    }

    //initialize and set orig
    int orig[count];
    for (int i = 1; i < count; i++)
    {
        orig[i] = numberarray[i];
    }

    //multiply by 2
    for (int i = 1; i < count; i += 2)
    {
        numberarray[i] = numberarray[i] * 2;
    }

    //declare new variables
    int check1 = 0;
    int check2 ;

    //Check algorithm to see what message to print
    //Will determine with check1 and check2 , output one of four messages

    //Visa condition (else invalid)
    if (count == 13)
    {
        for (int i = 0; i < count; i++)
        {
            check2  = (numberarray[i] % 10) + (numberarray[i] / 10 % 10);
            check1 = check1 + check2 ;
        }

        if (orig[12] == 4 && check1 % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //AMEX condition (else invalid)
    if (count == 15)
    {
        for (int i = 0; i < count; i++)
        {
            check2  = (numberarray[i] % 10) + (numberarray[i] / 10 % 10);
            check1 = check1 + check2 ;
        }

        if (orig[14] == 3 && check1 % 10 == 0 && (orig[13] == 4 || orig[13] == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //Visa other condition or mastercard, since they share this algorithm (else invalid)
    if (count == 16)
    {
        for (int i = 0; i < count; i++)
        {
            check2  = (numberarray[i] % 10) + (numberarray[i] / 10 % 10);
            check1 = check1 + check2 ;
        }

        if (orig[15] == 4 && check1 % 10 == 0)
        {
            printf("VISA\n");
        }
        else if (orig[15] == 5 && check1 % 10 == 0 && (orig[14] == 1 || orig[14] == 2 ||
                 orig[14] == 3 || orig[14] == 4 || orig[14] == 5))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    return 0;
}