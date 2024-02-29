#include <stdio.h>
#include "../includes/LinkedList.h"
#include "../includes/Server.h"
#include "../includes/ErrorCodes.h"

#define SERVER_PORT 8080

void createServer(Server* pServer) {
    // port/addr setup
    pServer->addr.sin_family = AF_INET;
    pServer->addr.sin_addr.s_addr = INADDR_ANY;
    pServer->addr.sin_port = htons(8080 );

    pServer->socket = socket(AF_INET, SOCK_STREAM, 0);

    if (pServer->socket == INVALID_SOCKET) {
        printf("Could not create socket : %d\n", WSAGetLastError());
    }

    ServerInit(pServer);
}

int main(int argc, char const** argv) {

    // --------------------------- Server
    Server serverInfo;
    // return error code if WinSock startuo fails
    if (WSAStartup(MAKEWORD(2, 2), &serverInfo.wsaData)){
        return WINSOCK_INIT_ERR;
    }
    createServer(&serverInfo);

    // --------------------------- Client
    ClientNode* clients = NULL;

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
    printf("\n\nReceived: %s", buffer);

    // send data, ok responds
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    send(new_socket, response, strlen(response), 0);

    ServerClose(&serverInfo);

    return 0;
}
