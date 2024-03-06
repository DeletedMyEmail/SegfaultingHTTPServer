#include <stdio.h>
#include "../includes/SocketIO.h"
#include "../includes/Server.h"
#include "../includes/ErrorCodes.h"
#include "../includes/Client.h"
#include "../includes/HashTable.h"

void onGet(Client pClient, HTTPRequest pRequest) {
    puts("get");
}

int main(int argc, char const** argv) {
    /*
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

    return 0;*/
    // Erstellen Sie eine neue Hashtabelle
    ht* table = ht_create();
    if (table == NULL) {
        printf("Failed to create hash table\n");
        return 1;
    }

    // Fügen Sie einige Schlüssel mit demselben Hashwert hinzu
    const char* key1 = "collision1";
    const char* key2 = "collision1";
    const char* key3 = "collision2";

    printf("%s\n", ht_set(table, key1, "value1"));
    printf("%s\n", ht_set(table, key2, "value2"));
    printf("%s\n", ht_set(table, key3, "value3"));

    // Überprüfen Sie die Werte
    printf("Key: %s, Value: %s\n", key1, (char*)ht_get(table, key1));
    printf("Key: %s, Value: %s\n", key2, (char*)ht_get(table, key2));
    printf("Key: %s, Value: %s\n", key3, (char*)ht_get(table, key3));

    // Zerstören Sie die Hashtabelle
    ht_destroy(table);

    return 0;
}
