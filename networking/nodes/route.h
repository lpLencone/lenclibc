#ifndef route_h
#define route_h

#include "http-server.h"
#include "../protocols/http-request.h"


struct route
{
    enum http_methods methods[9];
    char *uri;
    char *(*route_function)(struct http_server *server, struct http_req *http_req);
};


#endif /* route_h */