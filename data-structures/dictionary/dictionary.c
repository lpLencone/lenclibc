#include "dictionary.h"

struct dict *dictionary_init(int (*compare)(void *key_1, void *key_2))
{
    struct dict *dict = (struct dict *)malloc(sizeof(struct dict));
    dict->tree = bstree_init(compare);
    return dict;
}

int dictionary_insert(struct dict *dict, void *key, size_t key_size, void *val, size_t val_size)
{
    if (dict == NULL) {
        return NULL_ARGUMENT;
    }
    struct entry *entry = entry_init(key, key_size, val, val_size);
    bstree_insert(dict->tree, entry, sizeof(struct entry));
}

void *dictionary_search(struct dict *dict, void *key)
{
    void *result = bstree_search(dict->tree, key);
    if (result != NULL) {
        return ((struct entry *)result)->val;
    }
    return NULL;
}

void dictionary_delete(struct dict *dict)
{
    bstree_delete(dict->tree);
    free(dict);
}