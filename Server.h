#ifndef HTTPINC_SERVER_H
#define HTTPINC_SERVER_H

#include <stdio.h>
#include <WinSock2.h>

struct Server {
    WSADATA wsaData;
    SOCKET socket;
    struct sockaddr_in info;
};

short ServerInit(const struct Server *server);
short ServerListen(const struct Server *server);

#endif HTTPINC_SERVER_H
