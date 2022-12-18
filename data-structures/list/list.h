#ifndef linked_list_h
#define linked_list_h

#include "../node/node.h"

#include <stddef.h> // size_t

#define NULL_ARGUMENT 11
#define EMPTY_LIST    12
#define OUT_OF_BOUNDS 13

struct list
{
    struct node *head;
    struct node *tail;
    int length;
};

int list_append(struct list *list, void *data, size_t size);
int list_insert(struct list *list, int at, void *data, size_t size);
void *list_retrieve(struct list *list, int at);
int list_pop_head(struct list *list);
int list_pop_tail(struct list *list);
int list_remove_from(struct list *list, int from);
int list_remove_data(struct list *list, void *data, size_t size);

struct list *list_init();
int list_destroy(struct list *list);

#endif /* linked_list_h */