#include "../includes/Server.h"

void print(ListNode* node) {
    printf("Key:%s\tValue:%s\n", ((HashTableEntry*) node->val)->key, (char*) ((HashTableEntry*) node->val)->val);
}

void testHTTP() {
    HTTPRequest* request = parseHTTP("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.68.0\r\nAgent: curl/7.68.1\r\n\r\na:Body Test");

    printf("Method:%s\n", request->method);
    printf("Path:%s\n", request->path);
    printf("Version:%s\n", request->version);
    printf("Body:%s\n", request->body);
    printf("\nHeaders:\n");

    for (int i = 0; i < request->headers->capacity; i++) {
        if (request->headers->entries[i] != NULL) {
            printf("Key:%s\tValue:%s\n", request->headers->entries[i]->key, (char*) request->headers->entries[i]->val);
        }
        llForeach(request->headers->overflowBuckets[i], print);
    }
}

int main(int argc, char const** argv) {
    testHTTP();

    /*/ --------------------------- Server
    Server server;
    // create server if WinSock init is successful
    if (WSAStartup(MAKEWORD(2, 2), &server.wsaData)){ return WINSOCK_INIT_ERR; }
    ServerCreate(&server);

    // start server if creation successful
    if (server.socket == INVALID_SOCKET) { return SOCK_CREATE_ERR; }
    ServerSetup(&server);

    // --------------------------- Client handling
    ServerRun(&server);*/

    return 0;
}
