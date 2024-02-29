#include <stdio.h>
#include "../includes/LinkedList.h"
#include "../includes/Server.h"

int main(int argc, char const** argv){

    /*struct sockaddr_in c;
    ClientNode* head = createNode(0, c);

    push(head, 2, c);
    pushAt(head, 1, 1, c);

    printf("Length: %d", length(head));
    printf("\nval: %llu", get(head, 1)->socket);*/


    Server serverInfo;
    ServerInit(&serverInfo);

    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    SOCKET new_socket;

    new_socket = accept(serverInfo.socket, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept failed with error code : %d\n", WSAGetLastError());
    } else {
        printf("Connection accepted\n");
    }

    // read data
    char buffer[1024];
    int bytes_received = recv(new_socket, buffer, sizeof(buffer)-1, 0);
    if ( bytes_received == SOCKET_ERROR) {
        printf("recv failed with error: %d\n", WSAGetLastError());
    }
    else {
        buffer[bytes_received] = '\0';
    }

    printf("Received: %s", buffer);

    ServerClose(&serverInfo);

    return 0;
}
