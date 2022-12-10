#include "server.h"
#include "http-request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void launch(struct Server *server)
{
    char buffer[30000];
    printf("Listening on port: %d....\n", server->port);
    while (1) {
        printf("====== WAITING FOR CONNECTION ======\n");
        unsigned int address_len = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_len);
        recv(new_socket, buffer, sizeof(buffer), 0);
        http_request_init(buffer);
        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 1000\n\n<!DOCTYPE html><html><head><title>Halo Wod</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body><h1>Homo dog</h1><p>Welcome to the internet, have a look around</p><br /></body>";
        send(new_socket, hello, strlen(hello), 0);
        close(new_socket);
    }
}

int main(void)
{
    srand(time(NULL));
    int port = 5000 + (rand() % 5000);
    struct Server *server = server_init(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch);
    

    server->launch(server);



    return 0;
}