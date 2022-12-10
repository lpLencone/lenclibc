#ifndef node_h
#define node_h

#include <stddef.h> // size_t

struct Node
{
    struct Node *prev;
    struct Node *next;
    void *data;
};

struct Node *node_init(void *data, size_t size);
void node_delete(struct Node *node);

#endif /* node_h */