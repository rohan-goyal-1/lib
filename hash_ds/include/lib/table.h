#ifndef TABLE_H
#define TABLE_H

#include <stddef.h>

typedef struct Entry {
    void* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** entries;
    size_t current_capacity;
    size_t max_capacity;
} HashTable;

HashTable* ht_create(size_t init_size);
void ht_insert(HashTable* ht, void* key, void* value);
void* ht_get(HashTable* ht, void* key);
void* ht_delete(HashTable* ht, void* key);
void ht_destroy(HashTable* ht);

#endif // TABLE_H
