#include "../includes/Server.h"
#include "../includes/ErrorCodes.h"

short ServerInit(Server *pServer) {
    // return error code if provided socket is invalid
    if (pServer->socket == INVALID_SOCKET) {
        return SOCK_CREATE_ERR;
    }

    // return error code if binding fails
    if (bind(pServer->socket, (const struct sockaddr *) &pServer->addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        printf("Binding failed with error code : %d\n", WSAGetLastError());
        return 1;
    }

    // return error code if listening fails
    if (listen(pServer->socket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error code : %d\n", WSAGetLastError());
        return LISTEN_ERR;
    }

    return 0;
}

void ServerClose(Server* pServer) {
    closesocket(pServer->socket);
    WSACleanup();
}