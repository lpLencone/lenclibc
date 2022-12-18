#ifndef binary_search_tree_h
#define binary_search_tree_h

#include "../node/node.h"

#define NULL_ARGUMENT    11
#define EMPTY_TREE       12
#define INVALID_ARGUMENT 13

struct bstree
{
    struct node *head;
    int (*compare)(void *data_1, void *data_2);
};

void *bstree_search(struct bstree *tree, void *data);
int bstree_insert(struct bstree *tree, void *data, size_t size);
int bstree_cmp_int(void *int_1, void *int_2);

struct bstree *bstree_init(int (*compare)(void *data_1, void *data_2));
int bstree_destroy(struct bstree *tree);

#endif /* binary_search_tree_h */