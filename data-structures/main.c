#include "./list/list.h"
#include "./queue/queue.h"
#include "./dict/dict.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void list_example();
void queue_example();
void dict_example();

int main(void)
{
    dict_example();
    return 0;
}

// working
void list_example()
{
    struct list *list = list_init();
    int *data = (int *)malloc(sizeof(int));
    for (int i = 0; i < 12; i++) {
        *data = i;
        list_append(list, data, sizeof(int));
    }

    printf("nodes appended\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)list_retrieve(list, i));
    }
    puts("");

    list_pop_head(list);
    list_pop_tail(list);

    printf("nodes popped\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)list_retrieve(list, i));
    }
    puts("");

    *data = 4;
    list_remove_data(list, data, sizeof(int));
    *data = 6;
    list_remove_data(list, data, sizeof(int));
    list_remove_from(list, 3);
    list_remove_from(list, 5);

    printf("nodes removed\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)list_retrieve(list, i));
    }
    puts("");

    list_insert(list, 4, data, sizeof(int));
    *data = 10;
    list_insert(list, 2, data, sizeof(int));
    *data = -123;
    list_insert(list, 7, data, sizeof(int));

    printf("nodes inserted\n");

    for (int i = 0, len = list->length; i < len; i++) {
        printf("%d ", *(int *)list_retrieve(list, i));
    }
    puts("");

    list_delete(list);
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

void dict_example()
{
    srand(time(NULL));
    struct dict *dict = dict_init(dict_intcmp_keys);

    int *key = (int *)malloc(sizeof(int));
    float *val = (float *)malloc(sizeof(float));
    for (int i = 0; i < 20; i++) {
        *key = i;
        *val = rand() / (float) RAND_MAX * 100;
        printf("%d : %f\n", *key, *val);

        dict_insert(dict, key, sizeof(int), val, sizeof(float));
    }

    printf("\nentries inserted\n\n");

    for (int i = 0; i < 20; i++) {
        *key = i;
        printf("search for key %2d : ", *key);
        val = (float *)dict_search(dict, key, sizeof(int));
        if (val == NULL) {
            printf("none\n");
            continue;
        }
        printf("%f\n", *val);
    }

    dict_delete(dict);
}






