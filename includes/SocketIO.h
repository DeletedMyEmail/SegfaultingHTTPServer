#ifndef HTTPINC_SOCKETIO_H
#define HTTPINC_SOCKETIO_H

#include "LinkedList.h"
#include "HTTPRequest.h"

HTTPRequest parseHTTP(const char* pRequest);
void readDataFromClients(ListNode* pClients);

#endif //HTTPINC_SOCKETIO_H
