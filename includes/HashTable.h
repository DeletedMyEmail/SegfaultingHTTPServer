#ifndef _HT_H
#define _HT_H

#include <stddef.h>
#include "LinkedList.h"

typedef struct HashTableEntrey {
    char* key;
    void* val;
} HashTableEntry;

typedef struct HashTable {
    size_t capacity;
    size_t length;
    size_t itemSize;
    HashTableEntry** entries;
    LinkedList** overflowBuckets;
} HashTable;

HashTable* htCreate(size_t pCapacity);
void* htGet(HashTable* pTable, const char* pKey);
void htSet(HashTable* pTable, const char* pKey, void* pVal);
void htDelete(HashTable* pTable);
void htRemove(HashTable* pTable, const char* pKey);
void htDoubleCapacity(HashTable* pTable);

#endif // _HT_H