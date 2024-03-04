#include "../includes/SocketIO.h"
#include "../includes/Client.h"
#include <stdio.h>

void readDataFromClients(Node* pClients) {
    Node* currentNode = pClients;
    unsigned int i = 0;

    while (currentNode != NULL) {
        Client* client = currentNode->val;

        char buffer[1024];
        int bytes_received = recv(client->socket, buffer, sizeof(buffer) - 1, 0);
        // error
        if (bytes_received < 0) {
            // is error code just a timeout or an actual error
            if (WSAGetLastError() == WSAEWOULDBLOCK) {
                //printf("recv timed out %d\n", i);
            } else {
                printf("Reading failed: %d - Closing socket\n", WSAGetLastError());
                printf("%p\n", currentNode);
                currentNode = currentNode->next;
                free(popAt(&pClients, i));
                continue;
            }
        }
            // closed
        else if (bytes_received == 0) {
            currentNode = currentNode->next;
            free(popAt(&pClients, i));
            printf("Connection closed %d\n", i);
            continue;
        }
            // read
        else {
            buffer[bytes_received] = '\0';
            printf("\n\nReceived: %s\n", buffer);
            // send data, ok responds
            char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
            send(client->socket, response, strlen(response), 0);
        }

        currentNode = currentNode->next;
        ++i;
    }
}