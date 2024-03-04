#ifndef HTTPINC_LINKEDLIST_H
#define HTTPINC_LINKEDLIST_H

#include <winsock2.h>

typedef struct ListNode {
    void* val;
    struct ListNode* next;
} Node;

Node* createNode(void* pVal, size_t pSize);
Node* get(Node* pHead, unsigned int pPosition);
unsigned int length(Node* pHead);
void push(Node* pHead, void* pVal, size_t pSize);
void pushAt(Node* pHead, int pPosition, void* pVal, size_t pSize);
Node* pop(Node** pHead);
Node* popAt(Node** pHead, unsigned int pPosition);
void foreach(Node* pHead, void (*pCallback)(Node* pNode));

#endif //HTTPINC_LINKEDLIST_H
