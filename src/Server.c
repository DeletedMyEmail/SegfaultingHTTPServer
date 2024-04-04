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

int ServerRun(Server* pServer) {
    LinkedList* clients = llCreate();

    struct sockaddr_in socketAddr;
    int c = sizeof(struct sockaddr_in);
    SOCKET newSocket;

    while (1) {
        //printf("Waiting for incoming connections...\n" );

        // set socket to non-blocking
        u_long mode = 1;
        if (ioctlsocket(pServer->socket, FIONBIO, &mode) != NO_ERROR) {
            printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
            return 1;
        }

        newSocket = accept(pServer->socket, (struct sockaddr *)&socketAddr, &c);
        if (newSocket == INVALID_SOCKET) {
            // WSAEWOULDBLOCK means that accept would block if it was a blocking socket
            if (WSAGetLastError() != WSAEWOULDBLOCK) {
                printf("Accept failed with error code : %d\n", WSAGetLastError());
                break;
            }
        }
        else {
            Client* newClient = malloc(sizeof(Client));
            newClient->socket = newSocket;
            newClient->addr = socketAddr;

            if (clients->length == 0) {
                clients->head = createNode(newClient);
                clients->tail = clients->head;
                clients->length = 1;
            } else {
                llPush(clients, newClient);
            }

            printf("Connection accepted\n");
        }

        readDataFromClients(clients);
    }

    ServerClose(pServer);
}

void readDataFromClients(LinkedList* pClients) {
    printf("Size: %zu\n", pClients->length);
    ListNode* currentNode = pClients->head;
    unsigned int i = 0;

    while (currentNode != NULL) {
        Client* client = currentNode->val;
        char buffer[1024];
        int bytesReceived = recv(client->socket, buffer, sizeof(buffer) - 1, 0);

        // timeout - no msg
        if (WSAGetLastError() == WSAEWOULDBLOCK) {
            currentNode = currentNode->next;
        }
        // error
        else if (bytesReceived < 0) {
            printf("Reading failed: %d - Closing socket\n", WSAGetLastError());
            printf("%p\n", currentNode);
            currentNode = currentNode->next;
            free(llPopAt(pClients, i));
        }
        // close
        else if (bytesReceived == 0) {
            currentNode = currentNode->next;
            free(llPopAt(pClients, i));
            printf("Connection closed %d\n", i);
        }
        // read
        else {
            buffer[bytesReceived] = '\0';
            if (bytesReceived == sizeof(buffer) -1 ) {
                printf("Buffer full\n");
            }
            else {
                printf("\n\nReceived: %s\n", buffer);
            }

            // send data, ok responds
            char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
            send(client->socket, response, (int) strlen(response), 0);

            currentNode = currentNode->next;
            ++i;
        }
    }
}