#include "http-server.h"
#include "../protocols/http-request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void retrieve_page(struct http_req *http_req, int socket);

void launch(struct server *server)
{
    const int BUF_SIZE = 30000;
    char buffer[BUF_SIZE];
    socklen_t addrlen = sizeof(server->address);
    ssize_t bytes_read;
    printf("Listening on port %d...\n", server->port);
    while (1) {
        printf("\n\n====== Waiting for connection ======\n");
        int clientsock = accept(server->socket, (struct sockaddr *)&server->address, &addrlen);
        // Read client request
        bytes_read = recv(clientsock, buffer, BUF_SIZE, 0);
        buffer[bytes_read] = '\0';

        struct http_req *http_req = http_req_init(buffer);
        char *host = "Host";
        host = (char *)dict_search(http_req->header_fields, host, sizeof(char) * strlen(host));

        // // Send server response 1
        // char *resp_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 14\r\n\r\n";  
        // char resp[strlen(host) + strlen(resp_header)];
        // strcpy(resp, resp_header);
        // strcat(resp, host);
        // printf("host: %s\n", resp);
        // send(clientsock, resp, strlen(resp), 0);

        // Send server response 2
        retrieve_page(http_req, clientsock);

        // Close socket
        close(clientsock);
    }
}

void retrieve_page(struct http_req *http_req, int socket)
{
    char path[128];
    char *vars;
    char *uri = strtok_r(dict_search(http_req->request_line, "uri", sizeof("uri")), "?", &vars);
    
    strcpy(path, "/home/lencone/Documents/other");
    if (strcmp(uri, "/test") == 0) {
        strcat(path, uri);
    }
    else {
        strcat(path, "/index");
    }
    strcat(path, ".html");

    FILE *fp = fopen(path, "r");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // rewind(fp);

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, fp);
    fclose(fp);

    char resp[30000];
    strcpy(resp, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    strcat(resp, buffer);

    send(socket, resp, strlen(resp), 0);
    free(buffer);
}


