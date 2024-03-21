#ifndef HTTPINC_LINKEDLIST_H
#define HTTPINC_LINKEDLIST_H

#include <winsock2.h>

typedef struct ListNode {
    void* val;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
    ListNode* tail;
    size_t length;
} LinkedList;

LinkedList* llCreate();
ListNode* llGet(LinkedList* pList, unsigned int pPosition);
void llPush(LinkedList* pList, void* pVal);
void llPushAt(LinkedList* pList, int pPosition, void* pVal);
ListNode* llPop(LinkedList* pList);
ListNode* llPopAt(LinkedList* pList, unsigned int pPosition);
void llForeach(LinkedList* pList, void (*pCallback)(ListNode* pNode));
void llFree(LinkedList* pList);

#endif //HTTPINC_LINKEDLIST_H
