#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdint.h>

#define HEAP_SIZE 1024 * 1024

struct Block {
    size_t size;
    int free;
    struct Block *next;
};

extern uint8_t heap[HEAP_SIZE];
extern struct Block *free_list;
extern size_t total_allocated_memory;

void heap_init();
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);

#endif // ALLOCATOR_H
