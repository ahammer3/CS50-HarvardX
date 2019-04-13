// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <cs50.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

//define BUCKETS for hashTable
/* *** HASH FUNCTION / TABLE ADAPTED FROM ADAM CLARKSON, GITHUB. OC: NEEL MEHTA, STACKOVERFLOW *** */
#define BUCKETS 143091

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
