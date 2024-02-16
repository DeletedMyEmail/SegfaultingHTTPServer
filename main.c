#include <stdio.h>
#include "Server.h"

int main(int argc, char const** argv){
    struct Server serverInfo;

    ServerInit(&serverInfo);


    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    SOCKET new_socket;
    new_socket = accept(serverInfo.socket, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept failed with error code : %d", WSAGetLastError());
    } else {
        printf("Connection accepted\n");
    }

    ServerClose(&serverInfo);
    return 0;
}
