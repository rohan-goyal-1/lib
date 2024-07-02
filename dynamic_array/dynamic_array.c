#include "dynamic_array.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void array_create (DynamicArray *array, size_t item_size, size_t capacity) {
    array->data = malloc(item_size * capacity);
    array->item_size = item_size;
    array->curr_size = 0;
    array->capacity = capacity;
}

void array_resize (DynamicArray *array) {
    array->capacity *= 2;
    array->data = realloc(array->data, array->item_size * array->capacity);
}

void array_add (DynamicArray *array, void *element) {
    if (array->curr_size >= array->capacity) {
        array_resize(array);
    }
    void *target = (char *)array->data + (array->curr_size * array->item_size);
    memcpy(target, element, array->item_size);
    array->curr_size++;
}

void *array_get (DynamicArray *array, size_t index) {
    if (index >= array->curr_size) {
        fprintf(stderr, "DYNAMIC_ARRAY: Index out of bounds.");
        exit(1);
    }
    return array->data + (index * array->item_size);
}

void array_set (DynamicArray *array, size_t index, void *element) {
    if (index >= array->curr_size) {
        fprintf(stderr, "DYNAMIC_ARRAY: Index out of bounds.");
        exit(1);
    }
    void *target = (char *)array->data + (index * array->item_size);
    memcpy(target, element, array->item_size);
}

void array_remove (DynamicArray *array, size_t index) {
    if (index >= array->curr_size) {
        fprintf(stderr, "DYNAMIC_ARRAY: Index out of bounds.");
        exit(1);
    }
    void *target = (char *)array->data + (index * array->item_size);
    void *next = (char *)target + array->item_size;
    memmove(target, next, (array->curr_size - index - 1) * array->item_size);
    array->curr_size--;
}

void array_free (DynamicArray *array) {
    free(array->data);
    array->data = NULL;
    array->curr_size = 0;
    array->capacity = 0;
}
