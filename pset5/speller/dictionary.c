// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <strings.h>

#include "dictionary.h"

//global variable
int word_count=0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
// Returns true if word is in dictionary else false
bool check(const char *text_word)
{
    node *cursor=malloc(sizeof(node));
    if (cursor==NULL)
    {
        printf("memory error\n");
        return false;
    }
     unsigned int bucket= hash(text_word);
     if(table[bucket]==NULL)
     {
         return false;
     }
     strcpy(cursor->word, table[bucket]->word);
     cursor->next=table[bucket]->next;
     while (cursor!= NULL)
     {
         //if found
         if(strcasecmp(cursor->word, text_word)==0)
         {
            //free(cursor);
            return true;
         }
         cursor=cursor->next;
     }
     //free(cursor);
     return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //if word begins with uppercase
    if(word[0]<97)
    {
        unsigned int upper_index=word[0]-65;
        return upper_index;
    }
    unsigned int bucket_index=word[0]-97;
    //printf("bucket for word %s is %u\n", word, bucket_index);
    return bucket_index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *fp=fopen(dictionary, "r");
    char *word=malloc(sizeof(LENGTH));
    while (fscanf(fp, "%s", word) != EOF)
    {
        node *temp=malloc(sizeof(node));
        if(temp == NULL)
        {
            printf("memory error\n");
            return false;
        }
        unsigned int bucket= hash(word);
        if (table[bucket]==NULL)
        {
            strcpy(temp->word, word);
            temp->next=NULL;
            table[bucket]=temp;
            word_count++;
        }
        else
        {
            strcpy(temp->word, word);
            temp->next=table[bucket];
            table[bucket]=temp;
            word_count++;
        }
    }
    // debug loop
    // node *debug=malloc(sizeof(node));
    // debug=table[0];
    // for( int i= 0; i<9128; i++)
    // {
    //     printf("%s, ", debug->word);
    //     debug=debug->next;
    // }
    free(word);
    //fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //variables
    int freed=0;
    node *cursor=malloc(sizeof(node));
    node *temp=malloc(sizeof(node));
    if(cursor==NULL || temp==NULL)
    {
        printf("memory error\n");
        return false;
    }
    //loop through table
    for (int i=0; i<N; i++)
    {
        cursor=table[i];
        temp=table[i];
        while (cursor!=NULL)
        {
            temp=temp->next;
            free(cursor);
            cursor=temp;
            freed++;
        }    
    }
    if(freed==word_count)
    {
        free(cursor);
        free(temp);
        return true;
    }
    free(cursor);
    free(temp);
    return false;
}
