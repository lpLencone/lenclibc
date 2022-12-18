#include "http-server.h"
#include "route.h"

#include <stdarg.h>
#include <string.h>

void register_routes(struct http_server *server, char *(*route_function)(struct http_server *server, struct http_req *http_req), char *uri, int num_methods, ...);

void launch(struct server*);


struct http_server http_server_init()
{
    struct http_server server;
    server.server = server_init(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 4999, 10, launch);
    server.routes = dict_init(dict_strcmp_keys);
    server.register_routes = register_routes;
    return server;
}

void register_routes(struct http_server *server, char *(*route_function)(struct http_server *server, struct http_req *http_req), char *uri, int num_methods, ...)
{
    struct route route;
    va_list methods;
    va_start(methods, num_methods);
    for (int i = 0; i < num_methods; i++) {
        route.methods[i] = va_arg(methods, int);
    }
    strcpy(route.uri, uri);

    route.route_function = route_function;

    dict_insert(&server->routes, uri, sizeof(char) * strlen(uri), &route, sizeof(route));
}

