#include <stdio.h>
#include <cs50.h>

int main(void) //more comfortable
{
    int height; //declare variables for easier reading
    int line;
    int spaces;
    int hashes1;
    int hashes2;

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

        for (hashes1 = 0; hashes1 < line + 1; hashes1++) //for loop for 1st half of hashes
        {
            printf("#");
        }

        printf("  "); //2 spaces for the middle

        for (hashes2 = 0; hashes2 < line + 1; hashes2++) //for loop for 2nd half of hashes
        {
            printf("#");
        }

        printf("\n");
    }
}