#include <stdio.h>
#include <cs50.h>

int main(void) //less comfortable
{
    int height; //declare variables for easier reading
    int line;
    int spaces;
    int hashes;

    do //prompt user for number between 0 and 23
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);

    for (line = 0; line < height; line++) //main for loop for number of lines
    {
        for (spaces = height - line; spaces > 1; spaces--) //for loop for spaces
        {
            printf(" ");
        }

        for (hashes = 0; hashes < line + 2; hashes++) //for loop for 1st half of hashes
        {
            printf("#");
        }

        printf("\n");
    }
}