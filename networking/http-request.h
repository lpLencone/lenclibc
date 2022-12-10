#ifndef http_request_h
#define http_request_h

enum http_method
{
    GET, POST, PUT, HEAD, PATCH,
    DELETE, CONNECT, OPTIONS, TRACE
};

struct HTTPRequest
{
    enum http_method method;
    char *URI;
    float version;
};

struct HTTPRequest *http_request_init(char *request);

#endif /* http_request_h */