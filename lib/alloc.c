#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <memory.h>

#include "alloc.h"

int _allocator_initialized = 0;
int _verbose = 1;
void *start_ptr;
void *end_ptr;

struct mem_block_header {
    int free;
    int size;
};

void init_allocator(int capacity) {
    start_ptr = malloc(capacity);
    if (start_ptr == NULL) {
        _verbose && printf("Error during initialising allocator\n");
        exit(1);
    }
    struct mem_block_header header = {1, capacity - (int) sizeof(struct mem_block_header) };
    memcpy(start_ptr, &header, sizeof(struct mem_block_header));
    end_ptr = start_ptr + capacity;
    _allocator_initialized = 1;
    _verbose && printf("Allocator initialized \n");
    _verbose && printf("Amount of controlled memory: %d \n", capacity);
    _verbose && printf("Starting address: %p \n", start_ptr);
};

void destroy_allocator() {
    free(start_ptr);
    start_ptr = 0;
    end_ptr = 0;
    _allocator_initialized = 0;
    _verbose && printf("Allocator destroyed");
};

void *mem_alloc(size_t size){
    void *pos = start_ptr;
    while (pos != end_ptr) {

    }
    return NULL;
};

void *mem_realloc(void *addr, size_t size){

};

void mem_free(void *addr){

};