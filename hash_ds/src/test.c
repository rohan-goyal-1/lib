#include <stdio.h>

#include "../include/lib.h"

int main () {
    HashTable* table = ht_create(3);
    int k = 1, v = 5;
    ht_insert(table, &k, &v);
    printf("%d", *((int*)ht_get(table, &k)));
}
