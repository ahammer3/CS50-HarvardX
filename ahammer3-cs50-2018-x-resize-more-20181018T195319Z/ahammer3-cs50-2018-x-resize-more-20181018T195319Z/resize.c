// Resizes a .bmp by a factor of n (FLOAT)
//Uses copy.c as a template

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    //make second argument -> factor
    float factor = atof(argv[1]);
    if (factor < 0.0 || factor > 100.0)
    {
        fprintf(stderr, "factor must be between 1 and 100!");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Create new outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER bf_out = bf;
    BITMAPINFOHEADER bi_out = bi;

    //resize new dimension for output
    bi_out.biWidth *= factor;
    bi_out.biHeight *= factor;
    bi_out.biWidth = floor(bi_out.biWidth);
    bi_out.biHeight = floor(bi_out.biHeight);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Determine new image sizes
    bi_out.biSizeImage = (bi_out.biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(bi_out.biHeight);
    bf_out.bfSize = bf.bfSize - bi.biSizeImage + bi_out.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    //determine ratio
    double widthRatio = (double) bi.biWidth / (double) bi_out.biWidth;
    double heightRatio = (double) bi.biHeight / (double) bi_out.biHeight;

    //allocate mem to store one scanline
    RGBTRIPLE scanline[bi.biWidth * sizeof(RGBTRIPLE)];
    int scan = -1;

    // iterate over outfile's scanlines
    for (int i = 0, biHeight = abs(bi_out.biHeight); i < biHeight; i++)
    {
        //compute Y of corresponding row
        int row = i * heightRatio;

        //Read scanline (unless it's cached)
        if (scan != row)
        {
            fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                  (((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * row), SEEK_SET);
            fread(scanline, sizeof(RGBTRIPLE), bi.biWidth, inptr);
            scan = row;
        }

        //for all columns in the new image
        for (int j = 0; j < bi_out.biWidth; j++)
        {
            // compute X o corresponding column
            int column = j * widthRatio;
            fwrite(&scanline[column], sizeof(RGBTRIPLE), 1, outptr);
        }

        //Add new padding
        for (int k = 0; k < out_padding; k++)
        {
            fputc(0x00, outptr);
        }


        // skip over padding, if any
        // fseek(inptr, padding, SEEK_CUR);
    }

    //free(scanline);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}