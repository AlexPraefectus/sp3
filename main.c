#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#include "lib/alloc.h"

int ALLOCATION_SIZE = INT_MAX;

int main() {
    init_allocator(ALLOCATION_SIZE);
    destroy_allocator();
    return 0;
}