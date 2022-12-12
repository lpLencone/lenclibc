#include "list.h"

#include <stdlib.h>
#include <string.h>

struct node *__retrieve_node_at(struct list *list, int at);
struct node *__retrieve_node_by_data(struct list *list, void *data, size_t size);
void __remove_node(struct list *list, struct node *node);

struct list *list_init()
{
    struct list *list = (struct list *)malloc(sizeof(struct list));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

int list_delete(struct list *list)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    if (list->length != 0) {
        struct node *cursor = list->head;
        struct node *temp;
        while (cursor != NULL) {
            temp = cursor->next;
            node_delete(cursor);
            cursor = temp;
        }
    }
}

int list_append(struct list *list, void *data, size_t size)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    struct node *node = node_init(data, size);
    if (list->length == 0) {
        list->head = list->tail = node;
    }
    else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
    return 0;
}

int list_insert(struct list *list, int at, void *data, size_t size)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    else if (list->length == 0) {
        return EMPTY_LIST;
    }
    else if (at > list->length || at < -list->length) {
        return OUT_OF_BOUNDS;
    }
    struct node *node = node_init(data, size);
    if (list->length == 0) {
        list->head = list->tail = node;
    }
    else {
        struct node *cursor = __retrieve_node_at(list, at - 1);
        if (cursor == NULL) {
            list->head->prev = node;
            node->next = list->head;
            list->head = node;
        }
        else {
            if (cursor->next == NULL) {
                list->tail = node;
            }
            else {
                cursor->next->prev = node;
            }
            node->prev = cursor;
            node->next = cursor->next;
            cursor->next = node;
        }
    }
    list->length++;
    return 0;
}

void *list_retrieve(struct list *list, int at)
{
    if (list == NULL) {
        return (void *)NULL_ARGUMENT;
    }
    if (at > list->length || at < -list->length) {
        return (void *)OUT_OF_BOUNDS;
    }
    struct node *node = __retrieve_node_at(list, at);
    return node->data;
}

int list_pop_head(struct list *list)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    else if (list->length == 0) {
        return EMPTY_LIST;
    }
    __remove_node(list, list->head);
    return 0;
}

int list_pop_tail(struct list *list)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    else if (list->length == 0) {
        return EMPTY_LIST;
    }
    __remove_node(list, list->tail);
    return 0;
}

int list_remove_from(struct list *list, int at)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    else if (list->length == 0) {
        return EMPTY_LIST;
    }
    else if (at >= list->length || at < -list->length) {
        return OUT_OF_BOUNDS;
    }
    struct node *node = __retrieve_node_at(list, at);
    __remove_node(list, node);
    return 0;
}

int list_remove_data(struct list *list, void *data, size_t size)
{
    if (list == NULL) {
        return NULL_ARGUMENT;
    }
    else if (list->length == 0) {
        return EMPTY_LIST;
    }
    struct node *node = __retrieve_node_by_data(list, data, size);
    if (node == NULL) {
        return 1;
    }
    __remove_node(list, node);
    return 0;
}


// 
// PRIVATE FUNCTIONS
//

struct node *__retrieve_node_by_data(struct list *list, void *data, size_t size)
{
    struct node *cursor = list->head;
    while (cursor != NULL && memcmp(cursor->data, data, size) != 0) {
        cursor = cursor->next;
    }
    return cursor;
}

struct node *__retrieve_node_at(struct list *list, int at)
{
    struct node *cursor;
    if (at >= 0 && at < list->length / 2) {
        cursor = list->head;
        for (int i = 0; i < at; i++) {
            cursor = cursor->next;
        }
    }
    else if (at >= list->length / 2) {
        cursor = list->tail;
        for (int i = list->length - 1; i > at; i--) {
            cursor = cursor->prev;
        }
    }
    else if (at < 0 && at >= -list->length / 2) {
        cursor = list->tail;
        for (int i = -1; i > at; i--) {
            cursor = cursor->prev;
        }
    }
    else {
        cursor = list->head;
        for (int i = -list->length; i < at; i++) {
            cursor = cursor->next;
        }
    }
    return cursor;
}

void __remove_node(struct list *list, struct node *node)
{
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    else {
        list->head = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    else {
        list->tail = node->prev;
    }
    node_delete(node);
    list->length--;
}