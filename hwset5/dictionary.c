/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define HASHSIZE 1000000

int dictionarySize = 0;

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

node* hashtable[HASHSIZE] = {NULL};

// hash function
int hash (const char* word)
{
    int hashval = 0;
    int n;
    // iterate through each character in word
    for (int i = 0; word[i] != '\0'; i++)
    {
        // check if letter
        if(isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        hashval = ((hashval << 3) + n) % HASHSIZE;
    }
    return hashval;    
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // makes an all lower-cased copy of word
    char lower[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        lower[i] = tolower(word[i]);
    }
    lower[len] = '\0';
    
    int ind = hash(lower);
    
    // if hashtable is empty at ind
    if (hashtable[ind] == NULL)
    {
        return false;
    }
    
    // compare words
    node* cursor = hashtable[ind];
    while (cursor != NULL)
    {
        if (strcmp(lower, cursor->word) == 0)
        {
            // found a match
            return true;
        }
        cursor = cursor->next;
    }
    
    // didn't find word
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary
    FILE* infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    char word[LENGTH+1];
    
    // load each dictionary word into hash table
    while (fscanf(infile, "%s\n", word) != EOF)
    {
        // count total words
        dictionarySize++;
        
        // allocate dynamic memory
        node* thisWord = malloc(sizeof(node));
        
        // copy word into the new node
        strcpy(thisWord->word, word);
        
        // which bucket the word will go in
        int ind = hash(word);
        
        // if bucket is empty, put first entry
        if (hashtable[ind] == NULL)
        {
            hashtable[ind] = thisWord;
            thisWord->next = NULL;
        }else{
            // if bucket is not empty at index, add to end
            thisWord->next = hashtable[ind];
            hashtable[ind] = thisWord;
        }      
    }
    
    fclose(infile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarySize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through hashtable 
    for(int ind = 0; ind < HASHSIZE; ind++)
    {
        // free used nodes 
        while(hashtable[ind] != NULL)
        {
            node* cursor = hashtable[ind];
            hashtable[ind] = cursor->next;
            free(cursor);
        }
    }
    
    return true;
}