#include "queue.h"

#include <stdlib.h>

struct queue *queue_init()
{
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

int queue_delete(struct queue *queue)
{
    if (queue == NULL) {
        return NULL_ARGUMENT;
    }
    while (queue_pop(queue) != EMPTY_QUEUE);
    free(queue);
    return 0;
}

int queue_push(struct queue *queue, void *data, size_t size) {
    if (queue == NULL) {
        return NULL_ARGUMENT;
    }
    struct node *node = node_init(data, size);
    if (queue->last != NULL) {
        queue->last->next = node;
    }
    else {
        queue->first = node;
    }
    queue->last = node;
    return 0;    
}

int queue_pop(struct queue *queue)
{
    if (queue == NULL) {
        return NULL_ARGUMENT;
    }
    else if (queue->first == NULL) {
        return EMPTY_QUEUE;
    }
    struct node *node = queue->first;
    queue->first = node->next;
    node_delete(node);
    return 0;
}

void *queue_peek(struct queue *queue)
{
    if (queue == NULL || queue->first == NULL) {
        return NULL;
    }
    return queue->first->data;
}
