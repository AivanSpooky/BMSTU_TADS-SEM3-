#ifndef EXTERNAL_CT_H__

#define EXTERNAL_CT_H__

#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
} entry_t;

typedef struct {
    int size;
    int cnt;
    entry_t *table;
} hashtable_t;

hashtable_t* createExternalCacheHashTable(const char* filename);

bool findNumberInExternalCacheHashTable(hashtable_t* hashtable, int key, bool info);

void printHashtable(hashtable_t *ht);

void freeExternalCacheHashTable(hashtable_t* hashtable);

#endif