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
    LinkedList* requestHandler;
} Server;

typedef struct RequestHandler {
    char* method;
    void (*handlerFunc)(Client* pClient, HTTPRequest* pRequest);
} RequestHandler;

void ServerCreate(Server* pServer);
short ServerSetup(Server *pServer);
void ServerClose(Server* pServer);
int ServerRun(Server* pServer);

void ServerOn(Server* pServer, const char* pMethod, void (*handlerFunc)(Client* pClient, HTTPRequest* pRequest));

#endif //HTTPINC_SERVER_H
