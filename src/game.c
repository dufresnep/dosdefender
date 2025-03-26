// game.c
#include "game.h"
#include "particle.h" // Include particle.h to make Particle known
#include <allegro.h>

void init_game() {
    allegro_init(); // Initialize Allegro itself!  CRITICAL STEP
    set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0); // Set a graphics mode (corrected function name)
}

void update_game() {
    // Your game update logic here
}

void draw_game() {
    // Your game drawing code here
}

// Assuming particle_new belongs in particle.c, REMOVE it from here unless you have a VERY good reason to define it in both places.
/*
Particle* particle_new() {
    // Your particle creation logic here
    return NULL; // Or return the new particle
}
*/
