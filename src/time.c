// src/time.c
#include <time.h>
#include "time.h"

volatile tick_t ticks = 0; // Definition

tick_t get_tick(void) { // Corrected return type
    return clock();
}

uint32_t get_time(void) { // Corrected return type
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    return (uint32_t)time(NULL); // Returns the number of seconds since the Epoch
}
