#ifndef node_h
#define node_h

#include <stddef.h> // size_t

struct node
{
    struct node *prev;
    struct node *next;
    void *data;
};

struct node *node_init(void *data, size_t size);
void node_delete(struct node *node);

#endif /* node_h */