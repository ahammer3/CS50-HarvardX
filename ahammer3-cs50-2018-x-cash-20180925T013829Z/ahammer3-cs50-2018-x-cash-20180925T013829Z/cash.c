#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int n;  //store change value
    int counter;

    while (true)
    {
        printf("Change owed in dollars: \n"); //get input of change owed in float value
        change = get_float();

        if (change > 0)
        {
            break;
        }

    }

    n = round(change * 100);  //convert decimal to int and round to avoid flooring

    counter = 0;  //count the number of coins

    while (n >= 25)  //no quarters
    {
        n = n - 25;
        counter += 1;
    }

    while (n >= 10)  //no dimes
    {
        n = n - 10;
        counter += 1;
    }

    while (n >= 5)  //no nickels
    {
        n = n - 5;
        counter += 1;
    }

    printf("%d\n", counter + n); //prints the remainder n as pennies in 0-4 range

    return 0;
}