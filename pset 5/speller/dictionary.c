// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int word_len = strlen(word);
    char *word_enter = malloc((word_len + 1) * sizeof(char));
    for (int i = 0; i < word_len; i++)
    {
        word_enter[i] = tolower(word[i]);
    }
    word_enter[word_len] = '\0';
    int hash_value = hash(word_enter);
    node *address = table[hash_value];
    while (address != NULL)
    {
        if (strcmp(word_enter, address->word) == 0)
        {
            free(word_enter);
            return true;
        }
        address = address->next;
    }
    // TODO
    free(word_enter);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function]
    int word_len = strlen(word);
    int sum = 0;
    for (int i = 0; i < word_len; i++)
    {
        sum += tolower(word[i]) * i;
    }
    int calculated_hash = sum % N;
    return calculated_hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char *word = malloc((45 + 1) * sizeof(char));
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL || word == NULL)
    {
        printf("could not open the file\n");
        return false;
    }
    int words_left;
    while ((words_left = fscanf(dict, "%s", word)) != EOF)
    {
        node *word_copied = malloc(sizeof(node));
        if (word_copied == NULL)
        {
            free(word);
            printf("could not create a new node\n");
            return false;
        }
        int len = strlen(word);
        for (int i = 0; i < len; i++)
        {
            word_copied->word[i] = word[i];
        }
        word_copied->word[len] = '\0';
        int hash_val = hash(word);

        word_copied->next = table[hash_val];
        table[hash_val] = word_copied;
        word_count += 1;
    }
    fclose(dict);
    free(word);m
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
    // TODO
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *temp_address;
        int num = i;
        node *address = table[num];
        while (address != NULL)
        {
            temp_address = address;
            address = address->next;
            free(temp_address);
        }
    }
    // TODO
    return true;
}
