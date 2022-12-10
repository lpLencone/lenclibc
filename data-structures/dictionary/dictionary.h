#ifndef dictionary_h
#define dictionary_h

#include "../tree/binary-search-tree.h"
#include "entry.h"

struct dict
{
    struct bsearchtree *tree;
};

int dictionary_insert(struct dict *dict, void *key, size_t key_size, void *val, size_t val_size);
void *dictionary_search(struct dict *dict, void *key);

struct dict *dictionary_init(int (*compare)(void *key_1, void *key_2));
void dictionary_delete(struct dict *dict);

#endif /* dictionary_h */