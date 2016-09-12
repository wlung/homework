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
        printf("Error! Expected: ./caesar <positive integer>\n"); 
        return 1; // return 1 to signify error
        /* This will still accept things other than integers as input, but the 
        ** pset instrunctions say to "assume that the user will only type 
        ** integers at the prompt"
        */
    }
    
    // If the correct number of arguments is received, the program continues
    int k = atoi(argv[1]);
    if (k < 0)  // will still accept 0 even though that's not truly encrypted
    {
        printf("Error! Expected: ./caesar <positive integer>\n"); 
        return 1;
    }else if ((k%26) != 0){
        k %= 26;
    }
    
    // Get the plaintext to encrypt
    char* plaintext = GetString();
    
    // Encrypt plaintext using k
    int enval;
    for (int ii = 0; ii < strlen(plaintext); ii++)
    {
        if (isalpha(plaintext[ii]))
        {
            if (isupper(plaintext[ii])) // capital
            {
                // convert ASCII plaintext[ii] to indexed alphabet letter
                // add key
                // wrap around alphabet if indexed alphabet letter is past Z
                // convert back to ASCII
                enval = ((plaintext[ii] - 65 + k) % 26) + 65;
            }else if (islower(plaintext[ii])) // lowercase
            {
                // convert ASCII plaintext[ii] to indexed alphabet letter
                // add key
                // wrap around alphabet if indexed alphabet letter is past z
                // convert back to ASCII
                enval = ((plaintext[ii] - 97 + k) % 26) + 97;
            }
            printf("%c",enval);
        }else{ // keep non-letter characters the same
            printf("%c",plaintext[ii]);
        }
    }
    
    
    printf("\n"); 
    
    return 0; // indicate the program ran successfully
}