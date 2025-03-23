// include/time.h
#pragma once

#include <stdint.h>

typedef uint32_t tick_t; // Use uint32_t for ticks

tick_t get_tick(void);  // Return tick_t
uint32_t get_time(void); // Keep existing time functions
void usleep(uint32_t us);
void msleep(int ms);
extern volatile tick_t ticks;
