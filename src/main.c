#include <stdio.h>
#include "../includes/SocketIO.h"
#include "../includes/Server.h"
#include "../includes/ErrorCodes.h"
#include "../includes/Client.h"

int main(int argc, char const** argv) {
    // --------------------------- Server
    Server server;
    // create server if WinSock init is successful
    if (WSAStartup(MAKEWORD(2, 2), &server.wsaData)){ return WINSOCK_INIT_ERR; }
    ServerCreate(&server);

    // start server if creation successful
    if (server.socket == INVALID_SOCKET) { return SOCK_CREATE_ERR; }
    ServerSetup(&server);

    // --------------------------- Client handling
    Node* clients = NULL;

    struct sockaddr_in socketAddr;
    int c = sizeof(struct sockaddr_in);
    SOCKET newSocket;

    while (1) {
        //printf("Waiting for incoming connections...\n" );

        u_long mode = 1;
        if (ioctlsocket(server.socket, FIONBIO, &mode) != NO_ERROR) {
            printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
            return 1;
        }

        newSocket = accept(server.socket, (struct sockaddr *)&socketAddr, &c);
        if (newSocket == INVALID_SOCKET) {
            // WSAEWOULDBLOCK means that accept would block if it was a blocking socket
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                printf("Accept failed with error code : %d\n", WSAGetLastError());
                break;
            }
        } else {
            Client* newClient = malloc(sizeof(Client));
            newClient->socket = newSocket;
            newClient->addr = socketAddr;

            if (clients == NULL) {
                clients = createNode(newClient, sizeof(Client));
            } else {
                push(clients, newClient, sizeof(Client));
            }

            printf("Connection accepted\n");
        }

        readDataFromClients(clients);
    }

    ServerClose(&server);

    return 0;
}
