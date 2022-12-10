#include "binary-search-tree.h"

// struct node *__retrieve_node_by_data(struct bstree *tree, void *data, size_t size);
// void __remove_node(struct bstree *tree, struct node *node);
void __delete_tree_recursive(struct node *parent);

struct bstree *bstree_init(int (*compare)(void *data_1, void *data_2))
{
    struct bstree *tree = (struct bstree *)malloc(sizeof(struct bstree));
    tree->compare = compare;
    return tree;
}

void bstree_delete(struct bstree *tree)
{
    if (tree == NULL) {
        return NULL_ARGUMENT;
    }
    __delete_tree_recursive(tree->head);
    free(tree);
}

// shoud be private
struct node *iterate(struct bstree *tree, struct node *cursor, void *data, int *direction)
{
    if (tree->compare(cursor->data, data) == 1) {
        if (cursor->next != NULL) {
            iterate(tree, cursor->next, data, direction);
        }
        else {
            *direction = 1;
            return cursor;
        }
    }
    if (tree->compare(cursor->data, data) == -1) {
        if (cursor->prev != NULL) {
            iterate(tree, cursor->prev, data, direction);
        }
        else {
            *direction = -1;
            return cursor;
        }
    }
    else {
        *direction = 0;
        return cursor;
    }
}

void *bstree_search(struct bstree *tree, void *data)
{
    int direction;
    struct node *cursor = iterate(tree, tree->head, data, &direction);
    if (direction == 0) {
        return cursor->data;
    }
    return NULL;
}

void bstree_insert(struct bstree *tree, void *data, size_t size)
{
    int direction;
    struct node *cursor = iterate(tree, tree->head, data, &direction);
    struct node *node = node_init(data, size);
    if (direction == -1) {
        cursor->prev = &node;
    }
    else if (direction == 1) {
        cursor->next = &node;
    }
}

//
// PRIVATE FUNCTIONS
//
void __delete_tree_recursive(struct node *parent)
{
    if (parent == NULL) {
        return;
    }
    if (parent->prev != NULL) {
        __delete_tree_recursive(parent->prev);
    }
    if (parent->next != NULL) {
        __delete_tree_recursive(parent->next);
    }
    node_delete(parent);
}




