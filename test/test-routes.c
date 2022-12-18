#include "../data-structures/data-structures.h"
#include "../networking/networking.h"

void register_routes(struct http_server *server, char *(*route_function)(struct http_server *server, struct http_req *http_req), char *uri, int num_methods, ...);

struct http_server
{
    void (*register_routes)(struct http_server *server, char *(*route_function)(struct http_server *server, struct http_req *http_req), char *uri, int num_methods, ...)
};

char *render_template();

char *example(struct http_server *server, struct http_req *http_req)
{
    return render_template();
}

int main(void)
{
    struct http_server *server;
    server->register_routes(server, example, "/example", 2, 0, 1);
}