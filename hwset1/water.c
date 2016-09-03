#include <stdio.h>
#include <cs50.h>

int GetMinutes();

int main(void)
{
    int numMinutes = GetMinutes(); 
    int ounces = 192 * numMinutes; // shower spits 192 ounces of water per minute
    int numBottles = ounces/16; // 16 ounces in a bottle
    
    printf("bottles: %i\n", numBottles);
    
    return 0;
}

/**
 * Gets the length of the user's shower in minutes, as a positive integer
 * Based off source code from lecture 2, function-1.c, for GetPositiveInt()
 **/
int GetMinutes(void)
{
    int mins;
    do
    {
        printf("minutes: ");
        mins = GetInt();
    }
    while (mins < 1);
    return mins;
    
}