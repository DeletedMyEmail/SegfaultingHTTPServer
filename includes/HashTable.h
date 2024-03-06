#ifndef _HT_H
#define _HT_H

#include <stddef.h>
#include "LinkedList.h"

typedef struct {
    char* key;
    void* val;
} HashTableItem;

typedef struct {
    size_t capacity;
    size_t length;
    size_t itemSize;
    HashTableItem** items;
    ListNode** overflowBuckets;
} HashTable;

HashTable* htCreate(size_t pCapacity);
void* htGet(HashTable* pTable, const char* pKey);
void htSet(HashTable* pTable, const char* pKey, void* pVal);
void htInsert(HashTable* pTable, const char* pKey, void* pVal);
void htDoubleCapacity(HashTable* pTable);
void htDelete(HashTable* pTable);

#endif // _HT_H