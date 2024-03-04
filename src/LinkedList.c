#include "../includes/LinkedList.h"

Node* createNode(void* pVal, size_t pSize) {
    Node* node = malloc(pSize + sizeof(int*));
    node->val = pVal;
    node->next = NULL;

    return node;
}

void push(Node* pHead, void* pVal, size_t pSize) {
    Node* current = pHead;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(pSize + sizeof(int*));
    current->next->val = pVal;
    current->next->next = NULL;
}

void pushAt(Node* pHead, int pPosition, void* pVal, size_t pSize) {
    if (pPosition == 0) {
        Node* temp = pHead->next;
        pHead->next = malloc(pSize + sizeof(int*));
        pHead->next->next = temp;
        return;
    }

    Node* predecessorNode = get(pHead, pPosition - 1);
    Node* nextNode = predecessorNode->next;

    predecessorNode->next = malloc(pSize + sizeof(int*));
    predecessorNode->next->next = nextNode;
}

Node* popAt(Node** pHead, unsigned int pPosition) {
    if (pPosition == 0) {
        Node* temp = *pHead;
        *pHead = NULL;
        return temp;
    }

    Node* predecessorNode = get(*pHead, pPosition - 1);
    /*if (predecessorNode == NULL) {
        return;
    }*/

    Node* nodeToPop = predecessorNode->next;
    /*if (nodeToPop == NULL) {
        return;
    }*/

    predecessorNode->next = nodeToPop->next;
    return nodeToPop;
}

Node* pop(Node** pHead) {
    Node* current = *pHead;
    if (current->next == NULL) {
        Node* temp = *pHead;
        *pHead = NULL;
        return temp;
    }

    while (current->next != NULL) {
        current = current->next;
    }

    Node* temp = current->next;
    current->next = NULL;
    return temp;
}

Node* get(Node* pHead, unsigned int pPosition) {
    Node* current = pHead;

    while (current->next != NULL && pPosition > 0) {
        current = current->next;
        --pPosition;
    }
    if (pPosition > 0) {
        return NULL;
    }

    return current;
}

unsigned int length(Node* pHead) {
    if (pHead == NULL) {
        return 0;
    }

    unsigned int counter = 1;
    Node* current = pHead;

    while (current->next != NULL) {
        ++counter;
        current = current->next;
    }

    return counter;
}

void foreach(Node* pHead, void (*pCallback)(Node* pNode)) {
    Node* current = pHead;

    while (current != NULL) {
        pCallback(current);
        current = current->next;
    }
}