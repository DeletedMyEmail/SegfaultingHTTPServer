#ifndef HTTPINC_SERVER_H
#define HTTPINC_SERVER_H

#include <winsock2.h>
#include <stdio.h>

typedef struct Server {
    WSADATA wsaData;
    SOCKET socket;
    struct sockaddr_in addr;
} Server;

short ServerInit(Server *pServer);
void ServerClose(Server* pServer);

#endif //HTTPINC_SERVER_H
