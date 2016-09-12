/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;
int empty_loc [2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    
    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();
        
        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int i = 1;
    // use 2 for loops for a 2D array
    for(int row = 0; row < d; row++)
    {
        for(int col = 0; col < d; col++)
        {
            board[row][col] = d*d - i;
            i++;
        }
    }
    
    // if odd number of tiles, swap tiles numbered 1 and 2
    if((d*d-1)%2)
    {
        int temp = board[d-1][d-3];
        board[d-1][d-3] = board[d-1][d-2];
        board[d-1][d-2] = temp;
        printf("board[%i][%i] = %i\nboard[%i][%i] = %i",d-1,d-3,board[d-1][d-3],d-1,d-2,board[d-1][d-2]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop through and print each tile
    for(int row = 0; row < d; row++)
    {
        for(int col = 0; col < d; col++)
        {
            if(board[row][col] == 0)
            {
                // print blank tile
                printf("  _ ");
                
                //record blank tile's location
                empty_loc[0] = row;
                empty_loc[1] = col;
            }
            else
            {
                printf(" %2i ", board[row][col]);
            }
        }
        printf(" \n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // loop through board to find the tile
    for(int row = 0; row < d; row++)
    {
        for(int col = 0; col < d; col++)
        {
            if(tile == board[row][col])
            {
                //check if the tile borders the empty space
                if( ((row == empty_loc[0] - 1) && (col == empty_loc[1])) ||
                ((row == empty_loc[0]) && (col == empty_loc[1] - 1)) ||
                ((row == empty_loc[0]) && (col == empty_loc[1] + 1)) ||
                ((row == empty_loc[0] + 1) && (col == empty_loc[1])) )
                {
                    // move tile to empty space and move empty to old tile location
                    board[row][col] = 0;
                    board[empty_loc[0]][empty_loc[1]] = tile;
                    
                    // record location of new empty space
                    empty_loc[0] = row;
                    empty_loc[1] = col;
                    
                    // return true because tile can be legally moved
                    return true; 
                }
            }
        }
    }
    
    // return false because the given tile cannot be legally moved
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int i = 1;
    // loop through each tile to check if it has the winning value
    for(int row = 0; row < d; row++)
    {
        for(int col = 0; col < d; col++)
        {
            if(!((row == d-1) && (col == d-1)) && (board[row][col] != i))
            {
                return false;
            }else{
                i++;
            }
        }
    }
    
    // check that empty is in the bottom-right corner
    if(board[d-1][d-1] != 0)
    {
        return false;
    }
    
    return true;
}