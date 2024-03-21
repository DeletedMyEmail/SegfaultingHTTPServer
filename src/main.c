#include <stdio.h>
#include "../includes/SocketIO.h"
#include "../includes/Server.h"
#include "../includes/ErrorCodes.h"
#include "../includes/Client.h"
#include "../includes/HashTable.h"

void print(ListNode* x) {
    printf(": %p\n", x->val);
}

void LinkedListTest1() {
    LinkedList* ll = llCreate();

    int* x0 = malloc(sizeof(int));
    *x0 = 0;
    int* x1 = malloc(sizeof(int));
    *x1 = 1;
    int* x2 = malloc(sizeof(int));
    *x2 = 2;
    int* x3 = malloc(sizeof(int));
    *x3 = 3;

    llPush(ll, x0);
    llPush(ll, x2);
    llPushAt(ll, 1, x1);
    llPush(ll, x3);
    llPop(ll);

    llForeach(ll, print);

    printf("Length: %d\nGet1: %d\nGet2: %d\n\n",
           ll->length == 3,
           llGet(ll, 1)->val == (void*) 1,
           llGet(ll, 3) == NULL
    );

    llFree(ll);
}

void HashTableTest1() {
    HashTable* ht = htCreate(16);

    htDoubleCapacity(ht);
    printf("Capacity: %d\nGet without entries: %d\n",
           ht->capacity == 32,
           htGet(ht, "xyz") == NULL
    );

    int* i1 = malloc(sizeof(int));
    *i1 = 1;
    int* i2 = malloc(sizeof(int));
    *i2 = 2;
    int* i3 = malloc(sizeof(int));
    *i3 = 3;

    char* key1 = calloc(2, sizeof(char));
    key1[0] = 1;
    key1[1] = '\0';
    char* key2 = calloc(2, sizeof(char));
    key2[0] = 2;
    key2[1] = '\0';
    char* key3 = calloc(2, sizeof(char));
    key3[0] = 33;
    key3[1] = '\0';

    htSet(ht, key1, i1);
    htSet(ht, key2, i2);
    htSet(ht, key3, i3);

    printf("Get 1: %d\nGet 2: %d\nGet 2: %d\nLength: %d\n",
           *(int*)htGet(ht, key1) == 1,
           *(int*)htGet(ht, key2) == 2,
           *(int*)htGet(ht, key3) == 3,
           ht->length == 3
    );

    htDelete(ht);
}

int main(int argc, char const** argv) {
    //LinkedListTest1();
    HashTableTest1();
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

    return 0;
}
