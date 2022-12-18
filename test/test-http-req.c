#include "./networking/nodes/server.h"
#include "./networking/protocols/http-request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void launch(struct server *server)
{
    char buffer[1024];
    char *resp = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 1000\n\n<!DOCTYPE html><html><head><title>Halo Wod</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body><h1>Homo dog</h1><p>Welcome to the internet, have a look around</p><br></body>";
    unsigned int address_len = sizeof(server->address);
    printf("Listening on port: %d....\n", server->port);
    while (1) {
        printf("\n\n====== Waiting for connection ======\n");
        // Accept new socket
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_len);

        // Receive http request
        ssize_t bytes_read = recv(new_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_read] = '\0';
        printf("REQUEST :: length: %lu\n", strlen(buffer));
        for (int i = 0; buffer[i] != '\0'; i++) {
            printf("%c", buffer[i]);
            if (buffer[i] == '\n') printf("%3d ", i);
        }
        
        struct http_req *http_req = http_req_init(buffer);

        // Send back default response and terminate connection
        send(new_socket, resp, strlen(resp), 0);
        close(new_socket);

        http_req_delete(http_req);
    }
}

int main(void)
{
    srand(time(NULL));
    int port = 5000 + (rand() % 5000);
    struct server *server = server_init(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch);
    

    server->launch(server);

    return 0;
}