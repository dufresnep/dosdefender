// src/rand.c
#include "rand.h"
#include <stdlib.h>

uint32_t seed = 1;
int randn(void)
{
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % (RAND_MAX);
}

uint32_t randn_max(uint32_t upper){
     return ((uint32_t)randn() * upper) >> 15;
}
