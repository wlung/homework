#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    } while( (height < 0) || (height > 23));
    
    for(int ii = 0; ii < height; ii++)
    {
        for(int jj = 1; jj < (height-ii); jj++)
        {
            printf(" ");
        }
        for(int kk = 0; kk < (ii+1); kk++)
        {
            printf("#");
        }
        printf("  ");
        for(int kk = 0; kk < (ii+1); kk++)
        {
            printf("#");
        }
        printf("\n");
    }
    
    return 0;
}