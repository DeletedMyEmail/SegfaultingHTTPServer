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


void handleRequest(LinkedList* pRequestHandler, Client* pClient, HTTPRequest* pRequest) {
    if (pRequestHandler == NULL) {
        return;
    }

    ListNode* currentNode = pRequestHandler->head;

    while (currentNode != NULL) {
        RequestHandler* handler = (RequestHandler*) currentNode->val;
        if (strcmp(handler->method, pRequest->method) == 0) {
            handler->handlerFunc(pClient, pRequest);
            break;
        }
    }
}

void readDataFromClients(LinkedList* pClients, LinkedList* pRequestHandlers) {
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
            handleRequest(pRequestHandlers, client, parseHTTP(buffer));

            currentNode = currentNode->next;
            ++i;
        }
    }
}

void ServerOn(Server* pServer, const char* pMethod, void (*handlerFunc)(Client* pClient, HTTPRequest* pRequest)) {
    RequestHandler* handler = malloc(sizeof(RequestHandler));
    handler->method = strdup(pMethod);
    handler->handlerFunc= handlerFunc;

    if (pServer->requestHandler == NULL) {
        pServer->requestHandler = llCreate();
    }

    llPush(pServer->requestHandler, handler);
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

        readDataFromClients(clients, pServer->requestHandler);
    }

    ServerClose(pServer);
}