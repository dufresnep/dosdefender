// src/powerup.c
#include "powerup.h"
#include "vga.h"
#include "rand.h"
#include "ship.h"
#include "time.h"

extern struct ship *ships;
extern size_t ships_max;
extern struct powerup *powerups;
extern size_t powerups_max;

int powerup_drop(int32_t x, int32_t y)
{
    for (size_t i = 0; i < powerups_max; i++) {
        if (!powerups[i].alive) {
            powerups[i].x = x;
            powerups[i].y = y;
            powerups[i].birthtick = get_tick();
            powerups[i].alive = true;
            return i;
        }
    }
    return -1;
}
