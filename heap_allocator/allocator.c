#include <stdio.h>
#include <string.h>

#include "allocator.h"

uint8_t heap[HEAP_SIZE];
struct Block* free_list = (struct Block* )heap;

size_t total_allocated_memory = 0;

void heap_init () {
    free_list->size = HEAP_SIZE - sizeof(struct Block);
    free_list->free = 1;
    free_list->next = NULL;
}

void split (struct Block* fitting_slot, size_t size) {
    struct Block* new_block = (struct Block* )((uint8_t* )fitting_slot + size + sizeof(struct Block));
    new_block->size = fitting_slot->size - size - sizeof(struct Block);
    new_block->free = 1;
    new_block->next = fitting_slot->next;
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new_block;
}

void* malloc (size_t size) {
    struct Block* curr = free_list;
    while (curr != NULL) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(struct Block)) {
                split(curr, size);
            } 
            else {
                curr->free = 0;
            }
            total_allocated_memory += curr->size;
            return (void* )((uint8_t* )curr + sizeof(struct Block));
        }
        curr = curr->next;
    }
    return NULL;
}

void coalesce () {
    struct Block* curr = free_list;
    while (curr != NULL && curr->next != NULL) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size + sizeof(struct Block);
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
}

void free (void* ptr) {
    if (ptr != NULL) { 
        struct Block* block = (struct Block* )((uint8_t* )ptr - sizeof(struct Block));
        total_allocated_memory -= block->size;
        block->free = 1;
        coalesce();
    }
}

void* realloc (void* ptr, size_t size) {
    if (ptr == NULL) {
        return malloc(size);
    }
    struct Block* block = (struct Block* )((uint8_t* )ptr - sizeof(struct Block));
    if (block->size >= size) {
        return ptr;
    }
    void* new_ptr = malloc(size);
    if (new_ptr != NULL) {
        memcpy(new_ptr, ptr, block->size);
        free(ptr);
    }
    return new_ptr;
}
