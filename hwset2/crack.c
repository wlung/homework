#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>

int main(int argc, string argv[])
{
    // Give error if the program is executed without command-line arguments
    // or if there is more than one command-line argument
    if(argc!=2)
    {
        printf("Error! Expected: ./crack <password>\n"); // inform user of error
        return 1; // return non-zero int to signify error
    }
    
    // If the correct number of arguments is received, the program continues
    printf("\n"); // print password
    
    return 0; // indicate the program ran successfully
}