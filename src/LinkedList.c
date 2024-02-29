#include "../includes/LinkedList.h"

ClientNode* createNode(SOCKET pSocket, struct sockaddr_in pAddress) {
    ClientNode* node = malloc(sizeof(ClientNode));
    node->next = NULL;
    node->socket = pSocket;
    node->address = pAddress;

    return node;
}

void push(ClientNode* pHead, SOCKET pSocket, struct sockaddr_in pAddress) {
    ClientNode* current = pHead;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (ClientNode*)malloc(sizeof(ClientNode));
    current->next->socket = pSocket;
    current->next->address = pAddress;
    current->next->next = NULL;
}

void pushAt(ClientNode* pHead, int pPosition, SOCKET pSocket, struct sockaddr_in pAddress) {
    if (pPosition == 0) {
        ClientNode* temp = pHead->next;
        pHead->next = (ClientNode*)malloc(sizeof(ClientNode));
        pHead->next->socket = pSocket;
        pHead->next->address = pAddress;
        pHead->next->next = temp;
        return;
    }

    ClientNode* predecessorNode = get(pHead, pPosition - 1);
    ClientNode* nextNode = predecessorNode->next;

    predecessorNode->next = (ClientNode*)malloc(sizeof(ClientNode));
    predecessorNode->next->socket = pSocket;
    predecessorNode->next->address = pAddress;
    predecessorNode->next->next = nextNode;
}

void popAt(ClientNode* pHead, int pPosition) {
    ClientNode* predecessorNode = get(pHead, pPosition - 1);
    /*if (predecessorNode == NULL) {
        return;
    }*/

    ClientNode* nodeToPop = predecessorNode->next;
    /*if (nodeToPop == NULL) {
        return;
    }*/

    predecessorNode->next = nodeToPop->next;
}

void pop(ClientNode* pHead) {
    ClientNode* current = pHead;
    if (pHead->next == NULL) {
        pHead->next = NULL;
        return;
    }

    while (current->next->next != NULL) {
        current = current->next;
    }

    current->next = NULL;
}

ClientNode* get(ClientNode* pHead, unsigned int pPosition) {
    ClientNode* current = pHead;

    while (current->next != NULL && pPosition > 0) {
        current = current->next;
        --pPosition;
    }
    if (pPosition > 0) {
        return NULL;
    }

    return current;
}

unsigned int length(ClientNode* pHead) {
    if (pHead == NULL) {
        return 0;
    }

    unsigned int counter = 1;
    ClientNode* current = pHead;

    while (current->next != NULL) {
        ++counter;
        current = current->next;
    }

    return counter;
}