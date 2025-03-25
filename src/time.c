// src/time.c
#include "time.h"
#include <time.h>   // Add this line if using time
#include <allegro.h> // Add this Line

volatile tick_t ticks = 0; // Definition

tick_t get_tick(void) { // Corrected return type
    return (tick_t)(al_get_time() * 1000.0); // Convert seconds to milliseconds (ticks)
}

uint32_t get_time(void) { // Corrected return type
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    return (uint32_t)time(NULL); // Returns the number of seconds since the Epoch
}
