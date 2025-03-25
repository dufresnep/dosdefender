#ifndef POWERUP_H
#define POWERUP_H

#include <stdint.h>
#include <stdbool.h>
#include "rand.h"
#include "vga.h"

typedef enum {
    POWER_NONE,
    POWER_HEAL,
    POWER_FIRE_DELAY_DOWN,
    POWER_FIRE_DAMAGE_UP,
    POWER_TELEPORT,
    POWER_RADIUS_UP,
    POWER_RADIUS_DOWN,

} power_t;

struct powerup {
    int32_t x;
    int32_t y;
    uint8_t color;
    bool alive;
    power_t power;
    uint32_t birthtick;
};

extern int32_t powerups_max;

int powerup_drop(int32_t x, int32_t y);
#endif
