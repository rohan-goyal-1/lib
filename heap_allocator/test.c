#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "allocator.h"

void test_basic_allocation () {
    void* a = malloc(100);
    assert(a != NULL && "Basic allocation failed");
    printf("test_basic_allocation passed\n");
    free(a);
}

void test_multiple_allocations () {
    void* a = malloc(100);
    void* b = malloc(200);
    assert(a != NULL && b != NULL && a != b && "Multiple allocations failed");
    printf("test_multiple_allocations passed\n");
    free(a);
    free(b);
}

void test_free_and_reallocate () {
    void* a = malloc(100);
    free(a);
    void* b = malloc(100);
    assert(a == b && "Free and reallocate failed");
    printf("test_free_and_reallocate passed\n");
    free(b);
}

void test_reallocation () {
    void* a = malloc(100);
    strcpy((char *)a, "Test");
    void* b = realloc(a, 200);
    assert(b != NULL && strcmp((char *)b, "Test") == 0 && "Reallocation failed");
    printf("test_reallocation passed\n");
    free(b);
}

void test_zero_allocation () {
    void* a = malloc(0);
    assert(a != NULL && "Zero allocation failed");
    printf("test_zero_allocation passed\n");
    free(a);
}

void test_null_free () {
    free(NULL);
    printf("test_null_free passed\n");
}

void test_coalescing () {
    void* a = malloc(100);
    void* b = malloc(100);
    void* c = malloc(100);
    free(a);
    free(b);
    void* d = malloc(200);
    assert(a == d && "Coalescing failed");
    printf("test_coalescing passed\n");
    free(c);
    free(d);
}

int main () {
    heap_init();

    test_basic_allocation();
    test_multiple_allocations();
    test_free_and_reallocate();
    test_reallocation();
    test_zero_allocation();
    test_null_free();
    test_coalescing();

    assert(total_allocated_memory == 0 && "Memory leak detected");

    return 0;
}
