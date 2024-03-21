#include <stdint-gcc.h>
#include <malloc.h>
#include <stdio.h>
#include "../includes/HashTable.h"

#define FNV_OFFSET 14695981039346656037U
#define FNV_PRIME 1099511628211U

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

void createHashTableEntries(HashTable* pTable) {
    int capacity = pTable->capacity;
    HashTableEntry** entries = calloc(capacity, sizeof(HashTableEntry*));
    LinkedList** overflowBuckets = calloc(capacity, sizeof(LinkedList*));

    for (size_t i = 0; i < capacity; ++i) {
        entries[i] = NULL;
        overflowBuckets[i] = llCreate();
    }

    pTable->entries = entries;
    pTable->overflowBuckets = overflowBuckets;
}

HashTable* htCreate(size_t pCapacity) {
    HashTable* hashTable = malloc(sizeof(HashTable));
    hashTable->length = 0;
    hashTable->capacity = pCapacity;
    createHashTableEntries(hashTable);

    return hashTable;
}

void freeOverflowBuckets(LinkedList** pOverflowBuckets, size_t pCapacity) {
    for (size_t i = 0; i < pCapacity; ++i) {
        if (pOverflowBuckets[i] != NULL) {
            llFree(pOverflowBuckets[i]);
        }
    }

    free(pOverflowBuckets);
}

void htFreeEntries(HashTableEntry** pEntries, size_t pCapacity) {
    for (size_t i = 0; i < pCapacity; ++i) {
        if (pEntries[i] != NULL) {
            free(pEntries[i]->key);
            free(pEntries[i]->val);
            free(pEntries[i]);
        }
    }
}

void htDelete(HashTable* pTable) {
    freeOverflowBuckets(pTable->overflowBuckets, pTable->capacity);
    htFreeEntries(pTable->entries, pTable->capacity);
    free(pTable);
}

void htDoubleCapacity(HashTable* pTable) {
    size_t newCapacity = pTable->capacity * 2;
    HashTableEntry** newItemArr = calloc(newCapacity, sizeof(HashTableEntry*));
    LinkedList** newBuckets = calloc(newCapacity, sizeof(LinkedList*));

    for (size_t i = 0; i < pTable->capacity; ++i) {
        HashTableEntry* item = pTable->entries[i];
        newItemArr[i] = item;
        //free(pTable->entries[i]);
        newBuckets[i] = pTable->overflowBuckets[i];
        //free(pTable->overflowBuckets[i]);
    }
    for (size_t i = pTable->capacity; i < newCapacity; ++i) {
        newBuckets[i] = llCreate();
        newItemArr[i] = NULL;
    }

    pTable->capacity = newCapacity;
    pTable->overflowBuckets = newBuckets;
    pTable->entries = newItemArr;
}

HashTableEntry* createTableEntry(const char* pKey, void* pVal) {
    HashTableEntry* entry = malloc(sizeof(HashTableEntry));
    entry->val = pVal;
    entry->key = (char*) pKey;

    return entry;
}

void setEntryInBucket(HashTable* pTable, size_t pBucketIndex, const char* pKey, void* pVal) {
    LinkedList* bucket = pTable->overflowBuckets[pBucketIndex];
    ListNode* currentNode = bucket->head;

    while (currentNode != NULL) {
        HashTableEntry* entry = (HashTableEntry*) currentNode->val;

        if (strcmp(entry->key, pKey) != 0) {
            entry->val = pVal;
            return;
        }
        if (currentNode->next == NULL) {
            llPush(bucket, createTableEntry(pKey, pVal));
            ++pTable->length;
            return;
        }
        else {
            currentNode= currentNode->next;
        }
    }
}

void* getEntryInBucket(LinkedList* pBucket, const char* pKey) {
    ListNode* currentNode = pBucket->head;

    while (currentNode != NULL) {
        HashTableEntry* entry = (HashTableEntry*) currentNode->val;
        if (strcmp(entry->key, pKey) != 0) {
            return entry->val;
        }
        currentNode = currentNode->next;
    }

    return NULL;
}

void* htGet(HashTable* pTable, const char* pKey) {
    size_t index = hash_key(pKey) % pTable->capacity;

    if (pTable->entries[index] == NULL) {
        return NULL;
    }
    //printf("%s - %s\n", pTable->entries[index]->key, pKey);
    if (strcmp(pTable->entries[index]->key, pKey) == 0) {
        return pTable->entries[index]->val;
    }

    return getEntryInBucket(pTable->overflowBuckets[index], pKey);
}

void htSet(HashTable* pTable, const char* pKey, void* pVal) {
    size_t index = hash_key(pKey) % pTable->capacity;

    if (pTable->entries[index] == NULL) {
        pTable->entries[index] = malloc(sizeof(HashTableEntry));
        pTable->entries[index]->val = pVal;
        pTable->entries[index]->key = (char*) pKey;
        ++pTable->length;
    }
    else if (pTable->entries[index]->key == pKey) {
        pTable->entries[index]->val = pVal;
    }
    else {
        setEntryInBucket(pTable, index, pKey, pVal);
    }
}