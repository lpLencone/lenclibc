#ifndef dictionary_h
#define dictionary_h

#include "../bstree/bstree.h"
#include "entry.h"

struct dict
{
    struct bstree *tree;
};

int dict_insert(struct dict *dict, void *key, size_t key_size, void *val, size_t val_size);
void *dict_search(struct dict *dict, void *key, size_t key_size);

// Compare functions
int dict_strcmp_keys(void *entry_1, void *entry_2);
int dict_intcmp_keys(void *entry_1, void *entry_2);

// Constructor / destructor
struct dict *dict_init(int (*compare)(void *key_1, void *key_2));
int dict_delete(struct dict *dict);

#endif /* dictionary_h */