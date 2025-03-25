//src/burn.c
#include "particle.h"
#include <stddef.h> // Added
#include <powerup.h> // Added
void burn(int32_t x, int32_t y)
{
        // TODO: Replace with something better.
        for(size_t i=0; i<10; i++)
        {
                particle_new(x, y);
        }
}
