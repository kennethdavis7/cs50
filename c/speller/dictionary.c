// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];

int loaded_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char cp_word[LENGTH+1];
    strcpy(cp_word, word);
    for(int i = 0, n = strlen(cp_word); i < n; i++){
        cp_word[i] = tolower(cp_word[i]);
    }

    unsigned int hash_code = hash(cp_word);
    for(node *trav = table[hash_code]; trav != NULL; trav = trav->next){
        if(strcmp(trav->word, cp_word) == 0){
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for(int i = 0; word[i] != '\0'; i++){
        int multiply = 0;
        for(int j = i + 1; word[j] != '\0'; j++){
            multiply += word[j];
        }
        sum += word[i] + multiply;
    }
    return sum % N;
}

bool add_llist(const unsigned int hash_code, char *word){
    node *tmp = malloc(sizeof(node));
    if(tmp == NULL){
        return false;
    }

    strcpy(tmp->word, word);

    if(table[hash_code] == NULL){
        tmp->next = NULL;
    }
    else{
        tmp->next = table[hash_code];
    }

    table[hash_code] = tmp;
    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];
    // char *word = malloc(sizeof(char) * (LENGTH + 1));
    FILE *dictionary_file = fopen(dictionary, "r");

    if(dictionary_file == NULL){
        return false;
    }

    int index = 0, words = 0;

    char c;
    while(fread(&c, sizeof(char), 1, dictionary_file) == 1){
        if(c == '\n'){
            word[index] = '\0';
            words++;
            unsigned int hash_code = hash(word);
            bool add = add_llist(hash_code, word);
            if(!add){
                return false;
            }
            index = 0;
        }else{
            word[index] = c;
            index++;
        }
    }

    loaded_words = words;
    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return loaded_words;
}

void rm_llist(node *ptr){
    if(ptr == NULL){
        return;
    }

    rm_llist(ptr->next);

    free(ptr);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++){
        rm_llist(table[i]);
    }
    return true;
}
