#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <memory.h>

#include "alloc.h"

int _allocator_initialized = 0;
int _verbose = 1;
const int align = 4;
void *start_ptr;
void *end_ptr;

struct mem_block_header {
    int free;
    size_t size;
};

const unsigned long header_size = sizeof(struct mem_block_header);

void init_allocator(int capacity) {
    start_ptr = malloc(capacity);
    if (start_ptr == NULL) {
        _verbose && printf("Error during initialising allocator\n");
        exit(1);
    }
    struct mem_block_header header = {1, capacity - header_size };
    memcpy(start_ptr, &header, header_size);
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
    size_t allocation_size = (size % align == 0) ? size: size + 4 - (int)(size % align); // aligning allocated block to 4 bytes

    struct mem_block_header *cur_block = start_ptr; // starting from first block
    void *cur_block_ptr = cur_block;  // void pointer used for pointer arithmetic

    while (cur_block_ptr != end_ptr) {
        if (cur_block->free && cur_block->size >= allocation_size) {   // free and enough space
            // can we separate current block into two new ones?
            if (cur_block->size >= allocation_size + header_size + align){
                // calculating address of new block header
                struct mem_block_header *new_block_ptr = cur_block_ptr + header_size + allocation_size;

                // creating new block header
                struct mem_block_header new_block = {1, cur_block->size - header_size - allocation_size};
                *new_block_ptr = new_block;  // putting header to block start
                cur_block->size = allocation_size;  // resizing current block to allocation size
            }
            cur_block->free = 0; // marking block as taken
            return cur_block_ptr + header_size;
        }
        cur_block = cur_block_ptr + header_size + cur_block->size;
        cur_block_ptr = cur_block;
    }
    return NULL;
};

void *mem_realloc(void *addr, size_t size){
    if (addr == NULL) return mem_alloc(size);  // if no pointer was given just allocate new memory

    struct mem_block_header *old_header = addr - header_size;
    void *old_header_ptr = old_header;

    void *new_block_ptr = mem_alloc(size);  // trying to allocate new block
    if (!new_block_ptr) return NULL;  // we cannot reallocate memory to requested size
    memcpy(new_block_ptr, addr, old_header -> size);  // copy data to new block
    mem_free(addr);  // free block of memory
    return new_block_ptr;
};

void mem_free(void *addr){
    struct mem_block_header *current_header = addr - header_size;
    struct mem_block_header *next_block = addr + current_header->size;
    // concatenating blocks if next block is free
    if (next_block->free) {
        current_header->size = current_header->size + header_size + next_block->size;
    }
    current_header->free = 1;
};

void mem_dump(){
    const unsigned long chunk_size = 16;
    unsigned char byte;
    printf("Memory dump\n");
    for (unsigned long i = (unsigned long) start_ptr; i < (unsigned long) end_ptr ; i = i + chunk_size){
        printf("%lX\t", i);
        for (int j = 0; j < chunk_size; ++j) {
            byte = *(char *)(i + j);
            if (byte <= 0xF) {
                printf("0%X ", byte);
            }else {
                printf("%X ", byte);
            }
        }
        printf("\n");
    }
};