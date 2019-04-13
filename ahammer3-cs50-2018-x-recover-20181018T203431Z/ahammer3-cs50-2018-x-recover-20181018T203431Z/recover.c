#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

/* This program attempts to recover missing JPEGs from a forensic image included in the directory. */

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //create buffer
    unsigned char buffer[BUFFER_SIZE];

    //create counter
    int counter = 0;

    //declare picture outfile
    FILE *jpeg = NULL;

    //create bool for jpeg found
    bool jpeg_found = false;

    //loop through file until no more blocks
    while (fread(buffer, BUFFER_SIZE, 1, inptr) == 1)
    {
        //read first 4 bytes to check jpeg - last byte will be and-ing 0xe0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (jpeg_found)
            {
                //start a new pic
                fclose(jpeg);
            }
            else
            {
                //start writing (code below)
                jpeg_found = true;
            }

            //current pic - writes name as ###.jpg so we start at 001, etc.
            char file[8];
            sprintf(file, "%03d.jpg", counter);
            jpeg = fopen(file, "a");
            counter++;
        }

        if (jpeg_found)
        {
            //write
            fwrite(&buffer, BUFFER_SIZE, 1, jpeg);
        }
    }

    //close infile
    fclose(inptr);

    //close pic
    fclose(jpeg);

    //return
    return 0;
}