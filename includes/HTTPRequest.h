#ifndef HTTPINC_HTTPREQUEST_H
#define HTTPINC_HTTPREQUEST_H

#include "HashTable.h"

typedef struct HTTPRequest {
    char* raw;

    char* method;
    char* path;
    char* version;

    HashTable* headers;
    char* body;
} HTTPRequest;

HTTPRequest* parseHTTP(const char* pRequest);

#endif //HTTPINC_HTTPREQUEST_H
