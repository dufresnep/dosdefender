#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <allegro.h> // Add this

typedef uint32_t tick_t; // Define tick_t as uint32_t

extern volatile tick_t ticks; // Declaration

tick_t get_tick(void);
uint32_t get_time(void);

#endif
