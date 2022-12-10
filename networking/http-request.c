#include "http-request.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METHOD_AMOUNT 9
#define LONGEST_METHOD 8
const char METHOD_MAP[METHOD_AMOUNT][LONGEST_METHOD] = {"GET", "POST", "PUT", "HEAD", "PATCH", "DELETE", "CONNECT", "OPTIONS", "TRACE"};

struct HTTPRequest *http_request_init(char *request)
{
    char *separator = strstr(request, "\r\n\r\n");
    *(separator + 3) = '|';

    char *tokenptr = request;
    char *request_line = strtok_r(tokenptr, "\n", &tokenptr);
    char *header_fields = strtok_r(tokenptr, "|", &tokenptr);
    char *body = tokenptr;

    struct HTTPRequest *http_request;

    char *method = strtok_r(request_line, " ", &tokenptr);
    for (int i = 0; i < METHOD_AMOUNT; i++) {
        if (strcmp(method, METHOD_MAP[i]) == 0) {
            http_request->method = i;
            break;
        }
    }

    char *URI = strtok_r(tokenptr, " ", &tokenptr);
    http_request->URI = URI;

    char *http_version = strtok_r(tokenptr, " ", &tokenptr);
    strtok_r(http_version, "/", &http_version);
    http_request->version = strtof(http_version, NULL);

    printf("%f\n", http_request->version);

    return NULL;
}