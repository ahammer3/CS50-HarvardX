// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

// Define struct
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// array of nodes
node *hashTable[BUCKETS];

//get a word counter
unsigned int counter = 0;

//get a loaded state
bool loaded = false;

//hash function
/* *** HASH FUNCTION / TABLE ADAPTED FROM ADAM CLARKSON, GITHUB. OC: NEEL MEHTA, STACKOVERFLOW *** */
unsigned int hashWord(const char *word)
{
    unsigned long hash = 5381;
    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % BUCKETS;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //make copy
    int length = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        length++;
    }

    char wordCopy[length + 1];

    //to lowercase
    for (int i = 0; i < length; i++)
    {
        wordCopy[i] = tolower(word[i]);
    }

    //add null to end the word
    wordCopy[length] = '\0';

    //HASH THE WORD
    int hashed = hashWord(wordCopy);

    //assign pointer node
    node *ptr = hashTable[hashed];

    //check until end of linked list
    while (ptr != NULL)
    {
        if (strcmp(ptr -> word, wordCopy) == 0)
        {
            //we got a match!
            return true;
        }
        else
        {
            //not yet...
            ptr = ptr -> next;
        }
    }

    //default catch
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //init all to NULL
    for (int i = 0; i < BUCKETS; i++)
    {
        hashTable[i] = NULL;
    }

    //open dictionary
    FILE *file = fopen(dictionary, "r");

    //Scan through it
    while (true)
    {
        //allocate mem for new word
        node *newNode = malloc(sizeof(node));

        //mem error
        if (newNode == NULL)
        {
            fprintf(stderr, "Not enough memory. ABORT \n");
            return false;
        }

        //fscanf
        fscanf(file, "%s", newNode -> word);
        newNode -> next = NULL;

        //end of file
        if (feof(file))
        {
            free(newNode);
            break;
        }

        //word counter
        counter++;

        //HASH THE WORD
        int hashed = hashWord(newNode -> word);
        node *headNode = hashTable[hashed];

        //If empty bucket make first node
        if (headNode == NULL)
        {
            hashTable[hashed] = newNode;
        }
        else
        {
            newNode -> next = hashTable[hashed];
            hashTable[hashed] = newNode;
        }
    }

    //housekeeping
    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //return based on loaded
    if (loaded)
    {
        return counter;
    }
    else
    {
        return 0;
    }

    //default catch
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //unload loop
    for (int i = 0; i < BUCKETS; i++)
    {
        node *ptr = hashTable[i];
        while (ptr != NULL)
        {
            //kill
            node *temp = ptr;
            ptr = ptr -> next;
            free(temp);
        }
    }

    //change states
    loaded = false;
    return true;
}
