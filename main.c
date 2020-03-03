#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <memory.h>

#include "lib/alloc.h"

int ALLOCATION_SIZE = 200;

int main() {
    init_allocator(ALLOCATION_SIZE);
    int *pointers[4];
    mem_dump();
    printf("\n");
    pointers[0] = mem_alloc(16);
    memset(pointers[0], 255, 16);
    pointers[1] = mem_alloc(16);
    memset(pointers[1], 254, 16);
    pointers[2] = mem_alloc(16);
    memset(pointers[2], 253, 16);
    pointers[3] = mem_alloc(16);
    memset(pointers[3], 252, 16);
    mem_dump();
    mem_free(pointers[1]);
    mem_free(pointers[0]);
    mem_dump();
    pointers[2] = mem_realloc(pointers[2], 32);
    memset(pointers[2], 251, 32);
    mem_dump();
    destroy_allocator();
    return 0;
}