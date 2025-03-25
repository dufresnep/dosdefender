// src/bullet.c - No ship.h

#include "rand.h"
#include "bullet.h"
#include "particle.h"
#include "vga.h"
#include "game.h"

#include <stdlib.h>

#define BULLET_SPEED 4

void bullet_new(struct bullet *b, int32_t x, int32_t y, enum bullet_direction dir)
{
        b->x = x;
        b->y = y;
        b->dir = dir;
        b->active = 1;
}

void bullet_step(struct bullet *b, size_t id)
{
        if(!b->active)
                return;

        if(b->dir == bullet_left)
                b->x -= BULLET_SPEED;
        else
                b->x += BULLET_SPEED;

        // Out of bounds?
        if (b->x < 0 || b->x > 319) {
            b->active = 0;

            // 1/16 chance of powerup drop. Also not calling this
            //if (rand_number() > 64000)
            //    powerup_random(id);  // This function does not work, also removed
        }
}

void bullet_draw(struct bullet *b)
{
        if(!b->active)
        return;

        struct point p;
        p.x = b->x;
        p.y = b->y;
        vga_pixel(p, 15);
}
