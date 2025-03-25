// include/powerup.h
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "vga.h"
#include <stddef.h> // for size_t

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

extern size_t powerups_max = 50;
//void powerup_random(size_t id); // Defined in dosdef.c
int powerup_drop(int32_t x, int32_t y);
