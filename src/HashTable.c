#include <stdint-gcc.h>
#include <malloc.h>
#include "../includes/HashTable.h"

#define FNV_OFFSET 0
#define FNV_PRIME 0

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

ListNode** createOverflowBuckets(size_t pCapacity) {
    ListNode** overflowBuckets = calloc(pCapacity, sizeof(ListNode*));
    for (size_t i = 0; i < pCapacity; ++i) {
        overflowBuckets[i] = NULL;
    }

    return overflowBuckets;
}

HashTableItem** createHashTableEntries(size_t pCapacity) {
    HashTableItem** items = calloc(pCapacity, sizeof(HashTableItem*));
    for (size_t i = 0; i < pCapacity; ++i) {
        items[i] = NULL;
    }

    return items;
}

HashTable* htCreate(size_t pCapacity) {
    HashTable* hashTable = malloc(sizeof(HashTable));
    hashTable->length = 0;
    hashTable->capacity = pCapacity;
    hashTable->items = createHashTableEntries(pCapacity);
    hashTable->overflowBuckets = createOverflowBuckets(pCapacity);

    return hashTable;
}

void freeOverflowBuckets(ListNode** pOverflowBuckets, size_t pCapacity) {
    for (size_t i = 0; i < pCapacity; ++i) {
        if (pOverflowBuckets[i] != NULL) {
            llFree(pOverflowBuckets[i]);
        }
    }

    free(pOverflowBuckets);
}

void htFreeEntries(HashTableItem** pEntries, size_t pCapacity) {
    for (size_t i = 0; i < pCapacity; ++i) {
        if (pEntries[i] != NULL) {
            free(pEntries[i]->key);
            free(pEntries[i]->val);
            free(pEntries[i]);
            free(&pEntries[i]);
        }
    }
}

void delete(HashTable* pTable) {
    freeOverflowBuckets(pTable->overflowBuckets, pTable->capacity);
    htFreeEntries(pTable->items, pTable->capacity);
    free(pTable);
}

void htDoubleCapacity(HashTable* pTable) {
    size_t newCapacity = pTable->capacity * 2;
    HashTableItem** newItemArr = calloc(newCapacity, sizeof(HashTableItem*));

    for (size_t i = 0; i < pTable->capacity; ++i) {
        HashTableItem* item = pTable->items[i];
        newItemArr[i] = item;
        free(&pTable->items[i]);
    }

    pTable->capacity = newCapacity;
}

void* htGet(HashTable* pTable, const char* pKey);
void htSet(HashTable* pTable, const char* pKey, void* pVal);
void htInsert(HashTable* pTable, const char* pKey, void* pVal);