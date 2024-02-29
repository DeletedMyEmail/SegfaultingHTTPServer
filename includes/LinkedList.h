#ifndef HTTPINC_LINKEDLIST_H
#define HTTPINC_LINKEDLIST_H

#include <winsock2.h>

typedef struct ClientNode {
    SOCKET socket;
    struct sockaddr_in address;
    struct ClientNode* next;
} ClientNode;

ClientNode* createNode(SOCKET pSocket, struct sockaddr_in pAddress);
ClientNode* get(ClientNode* pHead, unsigned int pPosition);
unsigned int length(ClientNode* pHead);
void push(ClientNode* pHead, SOCKET pSocket, struct sockaddr_in pAddress);
void pushAt(ClientNode* pHead, int pPosition, SOCKET pSocket, struct sockaddr_in pAddress);
void pop(ClientNode* pHead);
void popAt(ClientNode* pHead, int pPosition);

#endif //HTTPINC_LINKEDLIST_H
