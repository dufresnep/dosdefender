// src/alloc.c
#include "alloc.h"

static char *heap = (char *)0x2000;
static char *brk = (char *)0x2000;
void *sbrk(size_t size)
{
    void *previous = brk;
    brk += size;
    if (brk > (heap + 0x8000))
        return (void *)-1;
    return previous;
}
