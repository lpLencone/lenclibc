#ifndef queue_h
#define queue_h

#include "../node/node.h"

#define NULL_ARGUMENT 11
#define EMPTY_QUEUE   12

#include <stddef.h> // size_t

struct Queue
{
    struct Node *first;
    struct Node *last;
    int length;
};

int queue_push(struct Queue *queue, void *data, size_t size);
int queue_pop(struct Queue *queue);
void *queue_peek(struct Queue *queue);

struct Queue *queue_init();
int queue_delete(struct Queue *queue);

#endif /* queue_h */