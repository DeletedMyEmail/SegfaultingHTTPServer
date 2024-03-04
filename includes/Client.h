#ifndef HTTPINC_CLIENT_H
#define HTTPINC_CLIENT_H

#include <winsock2.h>

typedef struct Client {
    SOCKET socket;
    struct sockaddr_in addr;
} Client;

#endif //HTTPINC_CLIENT_H
