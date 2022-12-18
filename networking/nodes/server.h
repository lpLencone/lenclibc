#ifndef server_h
#define server_h

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

struct server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct server *server);
};

struct server server_init(int domain, int service, int protocol, u_long interface, int port, int backlog, void (*launch)(struct server *server));

// void server_destroy(struct server *server);

#endif /* server_h */