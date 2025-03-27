#ifndef TIME_H
#define TIME_H

#include <stdint.h>  //it strangely make it like there is errors in defender.c/inlude Allegro
//#include "allegro/platform/astdint.h"
//#include <allegro.h> // Add this


typedef uint32_t tick_t;

uint32_t get_tick(void);
uint32_t get_time(void);

#endif
