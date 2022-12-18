#include "entry.h"

#include <stdlib.h> // malloc
#include <string.h> // memcpy

struct entry *entry_init(void *key, size_t key_size, void *val, size_t val_size)
{
    struct entry *entry = (struct entry *)malloc(sizeof(struct entry));
    entry->key = malloc(key_size);
    memcpy(entry->key, key, key_size);
    entry->val = malloc(val_size);
    memcpy(entry->val, val, val_size);
    return entry;
}

void entry_destroy(struct entry *entry)
{
    free(entry->key);
    free(entry->val);
    free(entry);
}