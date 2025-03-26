// src/time.c
#include <time.h>
#include "../include/timemy.h"

volatile tick_t ticks = 0; // Definition

uint32_t get_time(void) { // Corrected return type
    return (uint32_t)time(NULL); // Returns the number of seconds since the Epoch
}

uint32_t get_tick(void) { // Corrected return type
    return (uint32_t) clock();
}

