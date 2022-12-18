#ifndef http_server_h
#define http_server_h

#include "server.h"
#include "../protocols/http-request.h"

struct http_server
{
    struct server server;
    struct dict routes;
    void (*register_routes)(struct http_server *server, char *(*route_function)(struct http_server *server, struct http_req *http_req), char *uri, int num_methods, ...);
}; 

void launch(struct server *server);

struct http_server http_server_init();

#endif /* http_server_h */