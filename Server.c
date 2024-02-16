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
    if (bind(server->socket, (const struct sockaddr *) &server->info, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        printf("Binding failed with error code : %d", WSAGetLastError());
        return 1;
    }

    // return error code if listening fails
    if (listen(server->socket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error code : %d", WSAGetLastError());
        return LISTEN_ERR;
    }

    return 0;
}

void ServerClose(const struct Server* pServer) {
    closesocket(pServer->socket);
    WSACleanup();
}