#include <stdio.h>
#include "networking/nodes/http-server.h"

#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int port = 5000 + (rand() % 5000);
    struct server *server = server_init(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch);
    server->launch(server);
    server_delete(server);
    return 0;
}