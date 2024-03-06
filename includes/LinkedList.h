#ifndef HTTPINC_LINKEDLIST_H
#define HTTPINC_LINKEDLIST_H

#include <winsock2.h>

typedef struct ListNode {
    void* val;
    struct ListNode* next;
} ListNode;

ListNode* createNode(void* pVal, size_t pSize);
ListNode* get(ListNode* pHead, unsigned int pPosition);
unsigned int length(ListNode* pHead);
void push(ListNode* pHead, void* pVal, size_t pSize);
void pushAt(ListNode* pHead, int pPosition, void* pVal, size_t pSize);
ListNode* pop(ListNode** pHead);
ListNode* popAt(ListNode** pHead, unsigned int pPosition);
void foreach(ListNode* pHead, void (*pCallback)(ListNode* pNode));
void llFree(ListNode* pList);

#endif //HTTPINC_LINKEDLIST_H
