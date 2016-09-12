#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    // Give error if the program is executed without command-line arguments
    // or if there is more than one command-line argument
    if(argc!=2)
    {
        printf("Error! Expected: ./vigenere <keyword>\n"); 
        return 1; // return 1 to signify error
    } 
    
    int *k = malloc(sizeof(int) * strlen(argv[1]));
    
    // for each character of the argument
    for (int ii = 0; ii < strlen(argv[1]); ii++)
    {
        if (!isalpha(argv[1][ii]))
        {
            printf("Error! Expected keyword to only contain letters\n"); 
            return 1; // return 1 to signify error
        }
        else if(isupper(argv[1][ii]))
        {
            k[ii] = argv[1][ii] - 65;
        }
        else if(islower(argv[1][ii]))
        {
            k[ii] = argv[1][ii] - 97;
        }
        else // if there's any other cases not specified
        {
            printf("Error! Expected keyword to only contain letters\n"); 
            return 1; // return 1 to signify error
        }
    }
    
    // Get the plaintext to encrypt
    char* p = GetString();
    
     // Encrypt plaintext, p, using keyword
    int jj = 0; // index of keyword
    int enval; // encrypted letter
    for (int ii = 0; ii < strlen(p); ii++)
    {
        if (isalpha(p[ii]))
        {
            if (isupper(p[ii]))
            {
                // convert ASCII p[ii] to indexed alphabet letter
                // add keyword letter
                // wrap around alphabet if indexed alphabet letter is past Z
                // convert back to ASCII
                enval = ((p[ii] - 65 + k[jj]) % 26) + 65;
            }
            else if (islower(p[ii]))
            {
                // convert ASCII p[ii] to indexed alphabet letter
                // add keyword letter
                // wrap around alphabet if indexed alphabet letter is past z
                // convert back to ASCII
                enval = ((p[ii] - 97 + k[jj]) % 26) + 97;
            }
            
            // Print encrypted letter
            printf("%c",enval); 
            
            // Increment jj
            if (jj < (strlen(argv[1])-1))
            {
                jj++;
            }
            else if (jj == (strlen(argv[1])-1))
            {
                jj = 0;
            }
            else 
            {
                printf("Error incrementing through keyword\n");
                return 2;
            }
        }else{
            // keep non-letter characters the same
            printf("%c",p[ii]);
        }
    }
    
    printf("\n"); 
    return 0; // indicate successful run
}