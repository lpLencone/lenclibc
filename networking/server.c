#include "server.h"

#include <stdio.h>
#include <stdlib.h>

struct Server *server_init(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(struct Server *server))
{
    struct Server *server = (struct Server *)malloc(sizeof(struct Server));
    server->domain = domain;
    server->service = service;
    server->protocol = protocol;
    server->interface = interface;
    server->port = port;
    server->backlog = backlog;
    
    server->address.sin_family = domain;
    server->address.sin_port = htons(port);
    server->address.sin_addr.s_addr = htonl(interface);

    server->socket = socket(domain, service, protocol);
    if (server->socket == -1) {
        perror("Failed to create socket");
        exit(1);
    }
    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof(server->address)) == -1) {
        perror("Failed to bind socket");
        exit(1);
    }
    if (listen(server->socket, backlog) == -1) {
        perror("Failed to start listening");
        exit(1);
    }

    server->launch = launch;
    return server;
}

void server_delete(struct Server *server)
{
    free(server);
}




