#include <stddef.h>
#ifndef ALLOC_HEADER_FILE
#define ALLOC_HEADER_FILE

void init_allocator(int capacity);

void destroy_allocator();

void *mem_alloc(size_t size);

void *mem_realloc(void *addr, size_t size);

void mem_free(void *addr);

void mem_dump();

#endif

