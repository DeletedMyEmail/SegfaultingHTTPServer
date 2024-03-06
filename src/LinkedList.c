#include "../includes/LinkedList.h"

ListNode* createNode(void* pVal, size_t pSize) {
    ListNode* node = malloc(pSize + sizeof(int*));
    node->val = pVal;
    node->next = NULL;

    return node;
}

void push(ListNode* pHead, void* pVal, size_t pSize) {
    ListNode* current = pHead;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(pSize + sizeof(int*));
    current->next->val = pVal;
    current->next->next = NULL;
}

void pushAt(ListNode* pHead, int pPosition, void* pVal, size_t pSize) {
    if (pPosition == 0) {
        ListNode* temp = pHead->next;
        pHead->next = malloc(pSize + sizeof(int*));
        pHead->next->next = temp;
        return;
    }

    ListNode* predecessorNode = get(pHead, pPosition - 1);
    ListNode* nextNode = predecessorNode->next;

    predecessorNode->next = malloc(pSize + sizeof(int*));
    predecessorNode->next->next = nextNode;
}

ListNode* popAt(ListNode** pHead, unsigned int pPosition) {
    if (pPosition == 0) {
        ListNode* temp = *pHead;
        *pHead = NULL;
        return temp;
    }

    ListNode* predecessorNode = get(*pHead, pPosition - 1);
    /*if (predecessorNode == NULL) {
        return;
    }*/

    ListNode* nodeToPop = predecessorNode->next;
    /*if (nodeToPop == NULL) {
        return;
    }*/

    predecessorNode->next = nodeToPop->next;
    return nodeToPop;
}

ListNode* pop(ListNode** pHead) {
    ListNode* current = *pHead;
    if (current->next == NULL) {
        ListNode* temp = *pHead;
        *pHead = NULL;
        return temp;
    }

    while (current->next != NULL) {
        current = current->next;
    }

    ListNode* temp = current->next;
    current->next = NULL;
    return temp;
}

ListNode* get(ListNode* pHead, unsigned int pPosition) {
    ListNode* current = pHead;

    while (current->next != NULL && pPosition > 0) {
        current = current->next;
        --pPosition;
    }
    if (pPosition > 0) {
        return NULL;
    }

    return current;
}

unsigned int length(ListNode* pHead) {
    if (pHead == NULL) {
        return 0;
    }

    unsigned int counter = 1;
    ListNode* current = pHead;

    while (current->next != NULL) {
        ++counter;
        current = current->next;
    }

    return counter;
}

void foreach(ListNode* pHead, void (*pCallback)(ListNode* pNode)) {
    ListNode* current = pHead;

    while (current != NULL) {
        pCallback(current);
        current = current->next;
    }
}

void llFree(ListNode* pList) {
    ListNode* nextNode = pList;

    while (pList != NULL) {
        nextNode = pList->next;
        free(pList->val);
        free(pList);
        pList = nextNode;
    }
}