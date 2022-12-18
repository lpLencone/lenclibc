#include "bstree.h"

#include <stdlib.h>

struct node *__bstree_iterate(struct bstree *tree, struct node *cursor, void *data, int *direction);
void __destroy_tree_recursive(struct node *parent);

struct bstree *bstree_init(int (*compare)(void *data_1, void *data_2))
{
    struct bstree *tree = (struct bstree *)malloc(sizeof(struct bstree));
    tree->compare = compare;
    tree->head = NULL;
    return tree;
}

int bstree_destroy(struct bstree *tree)
{
    if (tree == NULL) {
        return NULL_ARGUMENT;
    }
    __destroy_tree_recursive(tree->head);
    free(tree);
}

void *bstree_search(struct bstree *tree, void *data)
{
    int direction;
    struct node *cursor = __bstree_iterate(tree, tree->head, data, &direction);
    if (direction == 0) {
        return cursor->data;
    }
    return NULL;
}

int bstree_insert(struct bstree *tree, void *data, size_t size)
{
    if (tree == NULL) {
        return NULL_ARGUMENT;
    }
    if (size < 1) {
        return INVALID_ARGUMENT;
    }
    struct node *node = node_init(data, size);
    if (tree->head == NULL) {
        tree->head = node;
    }
    else {
        int direction;
        struct node *cursor = __bstree_iterate(tree, tree->head, data, &direction);
        if (direction == -1) {
            cursor->prev = node;
        }
        else if (direction == 1) {
            cursor->next = node;
        }
    }
    return 0;
}

//
// PUBLIC HELPER FUNCTIONS
//
int bstree_cmp_int(void *int_1, void *int_2)
{
    if (*(int *)int_1 < *(int *)int_2) {
        return -1;
    }
    else if (*(int *)int_1 == *(int *)int_2) {
        return 0;
    }
    else {
        return 1;
    }
}

//
// PRIVATE FUNCTIONS
//
void __destroy_tree_recursive(struct node *parent)
{
    if (parent == NULL) {
        return;
    }
    if (parent->prev != NULL) {
        __destroy_tree_recursive(parent->prev);
    }
    if (parent->next != NULL) {
        __destroy_tree_recursive(parent->next);
    }
    node_destroy(parent);
}

struct node *__bstree_iterate(struct bstree *tree, struct node *cursor, void *data, int *direction)
{
    int result = tree->compare(cursor->data, data);
    if (result == -1) {
        if (cursor->prev != NULL) {
            __bstree_iterate(tree, cursor->prev, data, direction);
        }
        else {
            *direction = -1;
            return cursor;
        }
    }
    else if (result == 1) {
        if (cursor->next != NULL) {
            __bstree_iterate(tree, cursor->next, data, direction);
        }
        else {
            *direction = 1;
            return cursor;
        }
    }
    else {
        *direction = 0;
        return cursor;
    }
}




