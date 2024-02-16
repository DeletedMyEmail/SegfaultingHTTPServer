#include "Server.h"
#include "ErrorCodes.h"

short ServerInit(const struct Server *server) {
    // return error code if WinSock startuo fails
    if (WSAStartup(MAKEWORD(2, 2), &server->wsaData)){
        return WINSOCK_INIT_ERR;
    }

    // return error code if provided socket is invalid
    if (server->socket == INVALID_SOCKET) {
        return SOCK_CREATE_ERR;
    }

    // return error code if binding fails
    if (bind(server->socket, (const struct sockaddr *) &server->info, sizeof(server->info))) {

    }

    return 0;
}

short ServerListen(const struct Server *server) {
    return 0;
}