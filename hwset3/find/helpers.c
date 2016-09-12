/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    // binary searching algorithm
    int top = n;
    int bottom = 0;
    int middle;
    // printf("Searching. bottom = %i\ttop = %i\n", bottom, top);
    while(top >= bottom)
    {
        middle = bottom + (top - bottom) / 2;
        // printf("middle = %i\t", middle);
        if(array[middle] == value)
        {
            // printf("found value");
            return true;
        }else if (array[middle] < value)
        {
            //search indices greater than middle
            bottom = middle + 1;
            // printf("Searching greater indices. bottom = %i\ttop = %i\n", bottom, top);
        }else if (array[middle] > value)
        {
            //search indices less than middle
            top = middle - 1;
            // printf("Searching lower indices. bottom = %i\ttop = %i\n", bottom, top);
        }
    }
    
    // when the while loop is finished, the value isn't in the array 
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Loop through the array to sort values smallest to largest
    bool swap_flag = false;
    int i = 0;
    do
    {
        swap_flag = false;
        i++;
        
        for(int j = 0; j < n-i; j++)
        {
            // if the value is larger than the next value, swap the values
            if (values[j] > values[j+1])
            {
                int temp = values[j+1];
                values[j+1] = values[j];
                values[j] = temp;
                
                // indicate that a swap happened
                swap_flag = true;
            }
            // if the value is smaller than the next value or if they are equal,
            // do nothing because they are already in the correct order
            
        }
    }
    while(swap_flag);
    
    /**
    // print outs for checking sort
    for(i = 0; i < n; i++)
    { printf("%i\n",values[i]); }
    **/

    return;
}