#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

#define ARRAY_DEFAULT_INIT_SIZE 50

typedef struct {
    void *data;
    size_t item_size;
    size_t curr_size;
    size_t capacity;
} DynamicArray;

void array_create(DynamicArray *array, size_t item_size, size_t capacity);
void array_add(DynamicArray *array, void *element);
void *array_get(DynamicArray *array, size_t index);
void array_set(DynamicArray *array, size_t index, void *element);
void array_remove(DynamicArray *array, size_t index);
void array_free(DynamicArray *array);

#endif // DYNAMIC_ARRAY_H
