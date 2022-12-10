#include "./list/linked-list.h"
#include "./queue/queue.h"

#include <stdio.h>
#include <stdlib.h>

void list_example();
void queue_example();

int main(void)
{
    queue_example();
    return 0;
}

// working
void list_example()
{
    struct linkedlist *list = linkedlist_init();
    int *data = (int *)malloc(sizeof(int));
    for (int i = 0; i < 12; i++) {
        *data = i;
        linkedlist_append(list, data, sizeof(int));
    }

    printf("nodes appended\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)linkedlist_retrieve(list, i));
    }
    puts("");

    linkedlist_pop_head(list);
    linkedlist_pop_tail(list);

    printf("nodes popped\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)linkedlist_retrieve(list, i));
    }
    puts("");

    *data = 4;
    linkedlist_remove_data(list, data, sizeof(int));
    *data = 6;
    linkedlist_remove_data(list, data, sizeof(int));
    linkedlist_remove_from(list, 3);
    linkedlist_remove_from(list, 5);

    printf("nodes removed\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)linkedlist_retrieve(list, i));
    }
    puts("");

    linkedlist_insert(list, 4, data, sizeof(int));
    *data = 10;
    linkedlist_insert(list, 2, data, sizeof(int));
    *data = -123;
    linkedlist_insert(list, 7, data, sizeof(int));

    printf("nodes inserted\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)linkedlist_retrieve(list, i));
    }
    puts("");

    linkedlist_delete(list);
}

// working
void queue_example()
{
    struct queue *queue = queue_init();
    float *data = (float *)malloc(sizeof(float));
    for (int i = 0; i < 10; i++) {
        *data = 3.0 / (i + 1);
        queue_push(queue, data, sizeof(float));
    }

    printf("nodes pushed\n");
    
    while (queue->first != NULL) {
        printf("%f ", *(float *)queue_peek(queue));
        queue_pop(queue);
    }

    queue_delete(queue);
}

