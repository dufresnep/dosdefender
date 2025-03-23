// include/bullet.h
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "vga.h"
#include "ship.h"    // For struct ship

struct bullet {
    int32_t x;
    int32_t y;
    int32_t dx;
    int32_t dy;
    uint8_t color;
    bool alive;
    uint32_t birthtick;
    int32_t damage;
};

struct bullet bullet_create(int32_t x, int32_t y, int32_t dx, int32_t dy, uint8_t color);
void bullet_update(struct bullet *b);
void bullet_draw(struct bullet *b, bool clear);
void bullet_step(struct bullet *bullets, size_t num_bullets, struct ship *ships, size_t num_ships);
bool bullet_in_ship(struct bullet *b, struct ship *s);
