#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcpy

struct Node *node_init(void *data, size_t size)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->prev = NULL;
    node->next = NULL;
    node->data = malloc(size);
    memcpy(node->data, data, size);
    return node;
}

void node_delete(struct Node *node)
{    
    free(node->data);
    free(node);
}












