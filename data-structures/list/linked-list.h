#ifndef linked_list_h
#define linked_list_h

#include "../node/node.h"

#include <stddef.h> // size_t

#define NULL_ARGUMENT 11
#define EMPTY_LIST    12
#define OUT_OF_BOUNDS 13

struct LinkedList
{
    struct Node *head;
    struct Node *tail;
    int length;
};

int linkedlist_append(struct LinkedList *list, void *data, size_t size);
int linkedlist_insert_at(struct LinkedList *list, int at, void *data, size_t size);
void *linkedlist_retrieve(struct LinkedList *list, int at);
int linkedlist_pop_head(struct LinkedList *list);
int linkedlist_pop_tail(struct LinkedList *list);
int linkedlist_remove_from(struct LinkedList *list, int from);
int linkedlist_remove_data(struct LinkedList *list, void *data, size_t size);

struct LinkedList *linkedlist_init();
int linkedlist_delete(struct LinkedList *list);

#endif /* linked_list_h */