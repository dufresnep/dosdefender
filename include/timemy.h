#ifndef TIME_H
#define TIME_H

//#include <stdint.h>  //it strangely make it like there is errors in defender.c/inlude Allegro
#include <allegro.h> // Add this

uint32_t get_tick(void);
uint32_t get_time(void);

#endif
