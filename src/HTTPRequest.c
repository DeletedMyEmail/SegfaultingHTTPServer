#include "../includes/HTTPRequest.h"
#include <string.h>

HTTPRequest* parseHTTP(const char* pRequestStr) {
    HTTPRequest* request = malloc(sizeof(HTTPRequest));
    request->raw = strdup(pRequestStr);
    request->headers = htCreate(10);

    // parse first line

    request->body = strstr(request->raw, "\r\n\r\n");
    if (request->body != NULL) {
        request->body += 4;
    }

    char* keyBegin = strstr(request->raw, "\r\n") + 2;

    request->method = request->raw;
    char* endOfToken = strstr(request->raw, " ");
    endOfToken[0] = '\0';

    request->path = endOfToken + 1;
    endOfToken = strstr(request->path, " ");
    endOfToken[0] = '\0';

    request->version = endOfToken + 1;
    endOfToken = strstr(request->version, "\r\n");
    endOfToken[0] = '\0';

    // parse headers

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