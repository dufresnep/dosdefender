// include/powerup.h
#ifndef POWERUP_H
#define POWERUP_H

#include <stdint.h>
#include <stdbool.h>

struct powerup {
    int32_t x; // Use int32_t for consistency
    int32_t y; // Use int32_t for consistency
    int power;
    int birthtick; // Consider uint32_t if it's always positive
    bool alive;
};

// Function declarations
void powerup_drop(int32_t x, int32_t y); // Use int32_t
void update_powerup(); // Assuming this function exists

#endif
