#include "../includes/HTTPRequest.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

HTTPRequest* parseHTTP(const char* pRequestStr) {
    HTTPRequest* request = malloc(sizeof(HTTPRequest));
    request->raw = strdup(pRequestStr);
    request->headers = htCreate(10);
    request->method = NULL;
    request->path = NULL;
    request->version = NULL;

    request->body = strstr(request->raw, "\r\n\r\n");
    if (request->body != NULL) {
        request->body += 4;
    }

    char* keyBegin = strstr(request->raw, "\r\n") + 2;

    while (keyBegin > (char*) 2 && keyBegin < request->body - 2) {
        char* valBegin = strstr(keyBegin, ": ");
        valBegin[0] = '\0';
        valBegin += 2;

        char* valEnd = strstr(valBegin, "\r\n");
        if (valEnd != NULL) {
            valEnd[0] = '\0';
            htSet(request->headers, keyBegin, valBegin);
        }

        keyBegin = valEnd + 2;
    }

    return request;
}