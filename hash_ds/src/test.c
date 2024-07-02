#include <stdio.h>

#include "../include/lib.h"

#define TABLE_SIZE 10

unsigned long int hash (void* key) {
    int bytes = *(int*)key;
    return bytes % TABLE_SIZE;
}

int key_cmp (void* a, void* b) {
    return *(int*)a == *(int*)b;
}

int main () {
    HashTable* table = ht_create(TABLE_SIZE, &hash, &key_cmp);

    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr2[] = {11, 12, 13, 14, 15, 16, 17, 18};

    for (unsigned long i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        ht_insert(table, &arr1[i], &arr2[i]);
    }

    for (unsigned long i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        int value = *(int*)ht_get(table, &arr1[i]);
        printf("arr[%li]: %d\n", i, value);
    }
}
