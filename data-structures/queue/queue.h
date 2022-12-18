#ifndef queue_h
#define queue_h

#include "../node/node.h"

#define NULL_ARGUMENT 11
#define EMPTY_QUEUE   12

#include <stddef.h> // size_t

struct queue
{
    struct node *first;
    struct node *last;
};

int queue_push(struct queue *queue, void *data, size_t size);
int queue_pop(struct queue *queue);
void *queue_peek(struct queue *queue);

struct queue queue_init();
int queue_delete(struct queue *queue);

#endif /* queue_h */