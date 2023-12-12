#ifndef INTERNAL_HT_H__

#define INTERNAL_HT_H__

#define TABLE_SIZE 10
#define DEFAULT -1

#include <stddef.h>
// typedef struct {
//     int key;
//     int value;
//     int isCached;
// } cached_entry_t;

// typedef struct {
//     int size;
//     int cnt;
//     cached_entry_t *table;
// } cached_hashtable_t;

typedef struct HashEntry {
    int key;
    int value;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int size;
    HashEntry** table;
} ClosedAddressingHashTable;

size_t sizeofClosedAddressingHashTable(ClosedAddressingHashTable* hashtable);

int searchClosedAddressingHashTable(ClosedAddressingHashTable* hashtable, int key);

ClosedAddressingHashTable* createClosedAddressingHashTable(const char* filename);

void printClosedAddressingHashTable(ClosedAddressingHashTable* hashtable);

void freeClosedAddressingHashTable(ClosedAddressingHashTable* hashtable);



// int findNumberInInternalCacheHashTable(cached_hashtable_t* hashtable, int key);

// cached_hashtable_t* createInternalCacheHashTable(const char* filename);

// void printCachedHashtable(cached_hashtable_t *cht);

// void freeInternalCacheHashTable(cached_hashtable_t* hashtable);

#endif