#include "../includes/Server.h"
#include "../includes/ErrorCodes.h"

#define SERVER_PORT 8080

void ServerCreate(Server* pServer) {
    // port/addr setup
    pServer->addr.sin_family = AF_INET;
    pServer->addr.sin_addr.s_addr = INADDR_ANY;
    pServer->addr.sin_port = htons(SERVER_PORT );
    pServer->socket = socket(AF_INET, SOCK_STREAM, 0);
}

short ServerSetup(Server *pServer) {
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
