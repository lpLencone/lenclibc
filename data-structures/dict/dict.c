#include "dict.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dict *dict_init(int (*compare)(void *key_1, void *key_2))
{
    struct dict *dict = (struct dict *)malloc(sizeof(struct dict));
    dict->tree = bstree_init(compare);
    return dict;
}

int dict_insert(struct dict *dict, void *key, size_t key_size, void *val, size_t val_size)
{
    if (dict == NULL) {
        return NULL_ARGUMENT;
    }
    if (key_size < 1 || val_size < 1) {
        return INVALID_ARGUMENT;
    }
    struct entry *entry = entry_init(key, key_size, val, val_size);
    bstree_insert(dict->tree, entry, sizeof(struct entry));
}

void *dict_search(struct dict *dict, void *key, size_t key_size)
{
    int dummy_value = 0;
    struct entry *searchable = entry_init(key, key_size, (void *)&dummy_value, sizeof(dummy_value));

    // Use the iterate function of the BinarySearchTree to find the desired element.
    void *result = bstree_search(dict->tree, searchable);

    // Return either the value for that key or NULL if not found.
    if (result != NULL) {
        return ((struct entry *)result)->val;
    }
    else {
        return NULL;
    }
}

int dict_delete(struct dict *dict)
{
    if (dict == NULL) {
        return NULL_ARGUMENT;
    }
    bstree_delete(dict->tree);
    free(dict);
}

// PUBLIC HELPER FUNCTIONS
int dict_strcmp_keys(void *entry_1, void *entry_2)
{
    int cmp_result = strcmp((char *)(((struct entry *)entry_1)->key), 
                            (char *)(((struct entry *)entry_2)->key));
    if (cmp_result < 0) {
        return -1;
    }
    else if (cmp_result == 0) {
        return 0;
    }
    else {
        return 1;
    }
}