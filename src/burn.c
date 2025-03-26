// src/burn.c
#include <stddef.h>
#include "../include/powerup.h"
#include "../include/particle.h"

void burn(int32_t x, int32_t y)
{
        // TODO: Replace with something better.
        for(size_t i=0; i<10; i++)
        {
                particle_new(x, y);
        }
}
