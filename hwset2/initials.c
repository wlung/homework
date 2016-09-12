#include <cs50.h>
#include <stdio.h>
#include <string.h>

string GetName();
bool CheckBadChar(string str);
int IsLetter(char c);

int main(void)
{
    string name;
    do
    {
        name = GetName();
    }
    while(CheckBadChar(name));
    
    int initial = IsLetter(name[0]);
    if(initial)
    {
        printf("%c", initial);
    }
    
    for(int ii = 1; ii < strlen(name); ii++)
    {
        if((int) name[ii-1] == 32) 
        {
            initial = IsLetter(name[ii]);
            if(initial)
            {
                printf("%c", initial);
            }
        }
    }
    printf("\n");
    
    return 0;
}

// Getting a string after prompting user for a Name
string GetName(void)
{
    string name;
    do
    {
        // printf("Name: "); // CS50 checker doesn't want a prompt
        name = GetString();
    }
    while(name == NULL);
    
    return name;
}

// Checks is str contains a non-letter character other than space
bool CheckBadChar(string str)
{
    for(int ii = 0; ii < strlen(str); ii++)
    {
        // printf("%c\t%i\t%c\n",str[ii], (int) str[ii], str[ii]);
        if( ((int) str[ii] < 32) ||  // 32 = space
            ( ((int) str[ii] > 32) && ((int) str[ii] < 65) ) ||  // 65 = A
            ( ((int) str[ii] > 90) && ((int) str[ii] < 97) ) ||  // 90 = Z, 97 = a
            ((int) str[ii] > 122) )  // 122 = z
        {
            return true;
        }
    }
    
    return false;
}

// Check if char is a letter and turn into an initial if it is a letter
int IsLetter(char c)
{
    int letter = (int) c;
    
    if((letter > 64) && (letter < 91))  // A-Z
    {
        return letter;
    }else if ((letter > 96) && (letter < 123)) // a-z
    {
        letter -= 32;
        return letter;
    }else // not a letter
    {
        return 0; 
    }
}