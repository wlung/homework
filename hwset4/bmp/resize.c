/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember new size
    int n = atoi(argv[1]);
    
    // ensure proper n value was used
    if (n < 1 || n > 100)
    {
        printf("n must be between 1 and 100\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_in;
    fread(&bf_in, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_in;
    fread(&bi_in, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_in.bfType != 0x4d42 || bf_in.bfOffBits != 54 || bi_in.biSize != 40 || 
        bi_in.biBitCount != 24 || bi_in.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    
    // determine padding for scanlines
    int padding_in =  (4 - (bi_in.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    // create outfile's BITMAPINFOHEADER for resized image
    BITMAPINFOHEADER bi_out = bi_in;
    bi_out.biWidth *= n;
    bi_out.biHeight *= n;
    
    // determine padding for output
    int padding_out =  (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // calculate size to include pixels and padding, accounts for biHeight being negative
    bi_out.biSizeImage = (bi_out.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi_out.biHeight);
    
    
    // create outfile's BITMAPFILEHEADER for resized image
    BITMAPFILEHEADER bf_out = bf_in;
    // calculate new size
    bf_out.bfSize += bi_out.biSizeImage - bi_in.biSizeImage; 
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // array to store the RBBTRIPLEs in a row
    RGBTRIPLE row [bi_out.biWidth];
    
    // index of row array
    int row_ind = 0;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_in.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi_in.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // resize horizontally when writing to outfile
            for (int k = 0; k < n; k++)
            {            
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                row[row_ind] = triple;
                row_ind++;
            }
        }

        // reset row_ind
        row_ind = 0;
        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);

        // then add padding to output
        for (int k = 0; k < padding_out; k++)
        {
            fputc(0x00, outptr);
        }
        
        // resize vertically by adding additional rows
        for (int num_rows = 1; num_rows < n; num_rows++)
        {
            fwrite(&row, sizeof(RGBTRIPLE), bi_out.biWidth, outptr);
            
            // add padding
            for (int k = 0; k < padding_out; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
