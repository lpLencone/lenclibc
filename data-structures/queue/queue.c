#include "queue.h"

#include <stdlib.h>

struct Queue *queue_init()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->first = NULL;
    queue->last = NULL;
    queue->length = 0;
    return queue;
}

int queue_delete(struct Queue *queue)
{
    if (queue == NULL) {
        return NULL_ARGUMENT;
    }
    for (int i = 0, len = queue->length; i < len; i++) {
        queue_pop(queue);
    }
    free(queue);
}

int queue_push(struct Queue *queue, void *data, size_t size) {
    if (queue == NULL) {
        return NULL_ARGUMENT;
    }
    struct Node *node = node_init(data, size);
    if (queue->last != NULL) {
        queue->last->next = node;
    }
    else {
        queue->first = node;
    }
    queue->last = node;
    queue->length++;
    return 0;    
}

int queue_pop(struct Queue *queue)
{
    if (queue == NULL) {
        return NULL_ARGUMENT;
    }
    else if (queue->first == NULL) {
        return EMPTY_QUEUE;
    }
    struct Node *node = queue->first;
    queue->first = node->next;
    node_delete(node);
    queue->length--;
    return 0;
}

void *queue_peek(struct Queue *queue)
{
    if (queue == NULL) {
        return (void *)NULL_ARGUMENT;
    }
    else if (queue->first == NULL) {
        return (void *)EMPTY_QUEUE;
    }
    return queue->first->data;
}

