/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>
 
const int BLOCK_SIZE = 512;
 
int main(void)
{
    // open the forensic image file
    FILE* inptr = fopen("card.raw", "r");
    if(inptr == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    
    //create buffer to store one block of 512 bytes
    uint8_t buffer[BLOCK_SIZE];
    
    // keep count of number of output files
    int num = 0;
    
    // initialize the outfile pointer
    FILE *outptr = NULL;
    
    // read forensic image file until reach end of card
    while (fread(buffer, BLOCK_SIZE, 1, inptr))
    {
        // check for jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || 
            buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer[3] == 0xe5 || 
            buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer[3] == 0xe8 || 
            buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb || 
            buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee || 
            buffer[3] == 0xef))
        {
            // close outfile if it is currently open
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            
            // create jpeg file name
            char filename[8];
            sprintf(filename, "%03d.jpg", num);
                
            // open new jpeg file for writing out to 
            outptr = fopen(filename, "w");
            
            // increment num for the next file
            num++;
        }
        
        // write out recovered data
        if (outptr != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }
    
    // close files
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(inptr);
 
    return 0;
} 