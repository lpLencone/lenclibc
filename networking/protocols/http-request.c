#include "http-request.h"
#include "../../data-structures/stack/stack.h"
#include "../../data-structures/queue/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METHOD_AMOUNT 9
#define LONGEST_METHOD 8
const char METHOD_MAP[METHOD_AMOUNT][LONGEST_METHOD] = {"GET", "POST", "PUT", "HEAD", "PATCH", "DELETE", "CONNECT", "OPTIONS", "TRACE"};

void extract_request_line_fields(struct http_req *http_req, char *request_line);
void extract_header_fields(struct http_req *http_req, char *header_fields);
void extract_body(struct http_req *http_req, char *body);

struct http_req *http_req_init(char *request_string)
{
    // New request object.
    struct http_req *http_req = (struct http_req *)malloc(sizeof(struct http_req));

    char request_buf[strlen(request_string) + 1];
    strcpy(request_buf, request_string);
    // Find separator of the head and body of request
    char *separator = strstr(request_buf, "\r\n\r\n");
    *(separator)     = '|'; // Indicate end of header chunk
    *(separator + 3) = '|'; // Indicate start of body chunk

    // Separate the request string.
    char *tokenptr;
    char *request_line = strtok_r(request_buf, "\n", &tokenptr);
    char *header_fields = strtok_r(tokenptr, "|", &tokenptr);
    char *body = strtok_r(tokenptr, "|", &tokenptr);

    // Parse each section as needed.
    extract_request_line_fields(http_req, request_line);
    extract_header_fields(http_req, header_fields);
    extract_body(http_req, body);
    // Return the final product.
    return http_req;
}

int http_req_delete(struct http_req *http_req)
{
    if (http_req == NULL) {
        return NULL_ARGUMENT;
    }
    dict_delete(http_req->header_fields);
    dict_delete(http_req->request_line);
    dict_delete(http_req->body);
    free(http_req);
    return 0;
}

//
// PRIVATE FUNCTIONS
//
void extract_request_line_fields(struct http_req *http_req, char *request_line)
{
    // Copy the string literal into a local instance.
    char fields[strlen(request_line)];
    strcpy(fields, request_line);

    // Separate the string on spaces for each section.
    char *tokenptr;
    char *method = strtok_r(fields, " ", &tokenptr);
    char *uri = strtok_r(tokenptr, " ", &tokenptr);
    char *version = strtok_r(tokenptr, "\0", &tokenptr);

    // Insert the results into the request object as a dictionary.
    struct dict *request_line_dict = dict_init(dict_strcmp_keys);
    dict_insert(request_line_dict, "method", sizeof("method"), method, sizeof(char) * strlen(method));
    dict_insert(request_line_dict, "uri", sizeof("uri"), uri, sizeof(char) * strlen(uri));
    dict_insert(request_line_dict, "version", sizeof("version"), version, sizeof(char) * strlen(version));

    // Save the dictionary to the request object.
    http_req->request_line = request_line_dict;
    if (dict_search(http_req->request_line, "GET", sizeof("GET"))) {
        extract_body(http_req, (char *)dict_search(http_req->request_line, "uri", sizeof("uri")));
    }
}

void extract_header_fields(struct http_req *http_req, char *header_fields)
{
    // Copy the string literal into a local instance.
    char fields[strlen(header_fields)];
    strcpy(fields, header_fields);

    // Save each line of the input into a stack.
    char *tokenptr;
    struct stack *headers = stack_init();
    char *field = strtok_r(fields, "\n", &tokenptr);
    while (field != NULL) {
        stack_pile(headers, field, sizeof(char) * strlen(field));
        field = strtok_r(tokenptr, "\n", &tokenptr);
    }

    // Initialize the request's header_fields dictionary.
    http_req->header_fields = dict_init(dict_strcmp_keys);

    // Use the stack to further extract key value pairs.
    char *header = (char *)stack_peek(headers);
    while (header != (void *)EMPTY_STACK) {
        char *val;
        char *key = strtok_r(header, ":", &val);
        if (val != NULL) {
            // Remove leading white spaces.
            if (val[0] == ' ') {
                val++;
            }
            // Push the key value pairs into the request's header_fields dictionary.
            dict_insert(http_req->header_fields, key, sizeof(char) * strlen(key), val, sizeof(char) * strlen(val));
        }
        // Collect the next field from the stack.
        stack_ditch(headers);
        header = (char *)stack_peek(headers);
    }
    // Destroy the stack.
    stack_delete(headers);
}

// Parses the body according to the content type specified in the header fields.
void extract_body(struct http_req *http_req, char *body)
{
    // Check what content type needs to be parsed
    char *content_type = dict_search(http_req->header_fields, "Content-Type", sizeof("Content-Type"));
    if (content_type != NULL) {
        // Initialize the body_fields dictionary.
        struct dict *body_fields = dict_init(dict_strcmp_keys);
        if (strcmp(content_type, "application/x-www-form-urlencoded") == 0) {
            // Collect each key value pair as a set and store them in a queue.
            struct queue *fields = queue_init();
            char *field = strtok(body, "&");
            while (field != NULL) {
                queue_push(fields, field, sizeof(char) * strlen(field));
            }
            // Iterate over the queue to further separate keys from values.
            field = queue_peek(fields);
            while (field != NULL) {
                char *key = strtok(field, "=");
                char *val = strtok(NULL, "\0");
                // Remove unnecessary leading white space.
                if (val[0] == ' ') {
                    val++;
                }
                // Insert the key value pair into the dictionary.
                dict_insert(body_fields, key, sizeof(char) * strlen(key), val, sizeof(char) * strlen(val));
                // Collect the next item in the queue.
                queue_pop(fields);
                field = queue_peek(fields);
            }
            // Destroy the queue.
            queue_delete(fields);
        }
        else {
            // Save the data as a single key value pair.
            dict_insert(body_fields, "data", sizeof("data"), body, sizeof(char) * strlen(body));
        }
        // Set the request's body dictionary.
        http_req->body = body_fields;
    } /* content_type != NULL*/
    else {
        http_req->body = NULL;
    }
}








