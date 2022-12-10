#ifndef linked_list_h
#define linked_list_h

#include "../node/node.h"

#include <stddef.h> // size_t

#define NULL_ARGUMENT 11
#define EMPTY_LIST    12
#define OUT_OF_BOUNDS 13

struct linkedlist
{
    struct node *head;
    struct node *tail;
    int length;
};

int linkedlist_append(struct linkedlist *list, void *data, size_t size);
int linkedlist_insert(struct linkedlist *list, int at, void *data, size_t size);
void *linkedlist_retrieve(struct linkedlist *list, int at);
int linkedlist_pop_head(struct linkedlist *list);
int linkedlist_pop_tail(struct linkedlist *list);
int linkedlist_remove_from(struct linkedlist *list, int from);
int linkedlist_remove_data(struct linkedlist *list, void *data, size_t size);

struct linkedlist *linkedlist_init();
int linkedlist_delete(struct linkedlist *list);

#endif /* linked_list_h */