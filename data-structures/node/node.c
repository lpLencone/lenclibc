#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcpy

struct node *node_init(void *data, size_t size)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->prev = NULL;
    node->next = NULL;
    node->data = malloc(size);
    memcpy(node->data, data, size);
    return node;
}

void node_delete(struct node *node)
{    
    free(node->data);
    free(node);
}












