#ifndef HTTPINC_SERVER_H
#define HTTPINC_SERVER_H

#include <winsock2.h>
#include <stdio.h>
#include "Client.h"
#include "HTTPRequest.h"
#include "LinkedList.h"

typedef struct Server {
    WSADATA wsaData;
    SOCKET socket;
    struct sockaddr_in addr;
    void (*onGet)(Client pClient, HTTPRequest pRequest);
} Server;

void ServerCreate(Server* pServer);
short ServerSetup(Server *pServer);
void ServerClose(Server* pServer);
void readDataFromClients(LinkedList* pClients);
int ServerRun(Server* pServer);

#endif //HTTPINC_SERVER_H
