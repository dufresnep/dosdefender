// src/burn.c
#include <stddef.h> // Added
#include <powerup.h> // Added
#include "../include/particle.h" //ADD THE DEPENDENCY TO THE FUNCTION

void burn(int32_t x, int32_t y)
{
        // TODO: Replace with something better.
        for(size_t i=0; i<10; i++)
        {
                particle_new(x, y);
        }
}
