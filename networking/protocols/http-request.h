#ifndef http_request_h
#define http_request_h

#include "../../data-structures/dict/dict.h"

enum http_method
{
    GET, POST, PUT, HEAD, PATCH,
    DELETE, CONNECT, OPTIONS, TRACE
};

struct http_req
{
    struct dict *request_line;
    struct dict *header_fields;
    struct dict *body;
};

struct http_req *http_req_init(char *request_string);
int http_req_delete(struct http_req *http_req);

#endif /* http_request_h */