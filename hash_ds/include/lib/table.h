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

    unsigned long int (*hash) (void* key);
    int (*key_cmp) (void* a, void* b);
} HashTable;

HashTable* ht_create(size_t init_size, unsigned long int (*hash) (void* key), int (*key_cmp) (void* a, void* b));
void ht_insert(HashTable* ht, void* key, void* value);
void* ht_get(HashTable* ht, void* key);
void* ht_delete(HashTable* ht, void* key);
void ht_destroy(HashTable* ht);

#endif // TABLE_H
