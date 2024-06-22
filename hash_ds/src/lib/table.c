#include <stdlib.h>
#include <stdio.h>

#include "../../include/lib/table.h"

HashTable* ht_create (size_t init_size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));

    table->current_capacity = 0;
    table->max_capacity = init_size;

    table->entries = (Entry**) calloc(table->max_capacity, sizeof(Entry*));

    for (size_t i = 0; i < table->max_capacity; i++) {
        table->entries[i] = NULL;
    }

    return table;
}

void ht_destroy_entry (Entry* entry) {
    free(entry->key);
    free(entry->value);
    free(entry);
}

Entry* ht_create_entry (void* key, void* value) {
    Entry* entry = (Entry*) malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;
    return entry;
}

size_t ht_hash (void* key) {
    uint8_t* bytes = (uint8_t*)key;
    size_t hash = 0;

    for (size_t i = 0; i < sizeof(key); i++) {
        // TODO: better hashing function
        hash = 31 * hash + bytes[i]; 
    }

    return hash;
}

int ht_key_cmp (void* a, void* b) {
    // TODO: Update key comparison for all possible key types
    return (int*) a == (int*) b;
}

void ht_handle_collision (HashTable* ht, Entry* entry) {
    size_t index = ht_hash(entry->key);
    Entry* current = ht->entries[index];

    while (current->next != NULL) {
        if (ht_key_cmp(current->key, entry->key)) {
            current->value = entry->value;
            ht_destroy_entry(entry);
            return;
        }

        current = current->next;
    }
    current->next = entry;
    ht->current_capacity++;
}

void ht_insert (HashTable* ht, void* key, void* value) {
    Entry* entry = ht_create_entry(key, value);

    size_t index = ht_hash(key);
    Entry* curr_entry = ht->entries[index];

    if (curr_entry == NULL) {
        if (ht->current_capacity == ht->max_capacity) {
            fprintf(stderr, "ERROR: Max capacity of hash_table");
            ht_destroy_entry(curr_entry);
        }
        else {
            ht->entries[index] = entry;
            ht->current_capacity++;
        }
    }
    else {
        ht_handle_collision(ht, entry);
    }
}

void* ht_get(HashTable* ht, void* key) {
    size_t index = ht_hash(key);
    Entry* entry = ht->entries[index];

    while (entry != NULL) {
        if (ht_key_cmp(entry->key, key)) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

void* ht_delete (HashTable* ht, void* key) {
    size_t index = ht_hash(key);
    Entry* current = ht->entries[index];
    Entry* prev = NULL;

    while (current != NULL) {
        if (ht_key_cmp(current->key, key)) {
            void* return_value = current->value;
            if (prev == NULL) {
                ht->entries[index] = current->next;
            } 
            else {
                prev->next = current->next;
            }
            ht_destroy_entry(current);
            ht->current_capacity--;
            return return_value;
        }
        prev = current;
        current = current->next;
    }

    return NULL;
}

void ht_destroy (HashTable* ht) {
    for (size_t i = 0; i < ht->max_capacity; i++) {
        Entry* current = ht->entries[i];
        while (current != NULL) {
            Entry* next = current->next;
            ht_destroy_entry(current);
            current = next;
        }
    }

    free(ht->entries);
    free(ht);
}
