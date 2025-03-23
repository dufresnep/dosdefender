// burn.c
#include "burn.h"
#include "particle.h"
#include "vga.h"
#include "ship.h" //For MAX_PLAYERS
#include "dosdef.h" //For powerup_random

extern struct particle *particles;
extern size_t particles_max;

void burn(int32_t x, int32_t y)
{
    for (size_t i = 0; i < particles_max; i++) {
        if (!particles[i].alive) {
            particles[i].x = x;
            particles[i].y = y;
            particles[i].dx = 0;
            particles[i].dy = 0;
            particles[i].birthtick = 0;
            particles[i].color = 0; // Set a default color
			particles[i].alive = true;
            break;
        }
    }
}
