// src/game.c
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // For size_t definition if needed here
#include "../include/game.h"
// Include other necessary headers like powerup.h, bullet.h etc.
#include "../include/powerup.h"
#include "../include/bullet.h"
#include "../include/particle.h"
#include "../include/ship.h"


// Define global variables
struct ship *ships = NULL;
struct bullet *bullets = NULL;
struct particle *particles = NULL;
struct powerup *powerups = NULL;   // Define as pointer, initialize to NULL

size_t bullets_max = 100;
size_t particles_max = 200;
size_t powerups_max = 50;          // Define size here

unsigned long score = 0;

void init_game() {
    // ... (allocate memory for ships, bullets, particles) ...
    powerups = malloc(sizeof(struct powerup) * powerups_max);
    if (!powerups) {
        fprintf(stderr, "Memory allocation failed for powerups!\n");
        exit(1);
    }
    // Initialize powerups array (e.g., set all 'alive' to false)
    size_t i;
    for (i = 0; i < powerups_max; ++i) {
         powerups[i].alive = false;
    }

    // ... rest of init_game ...
}

// Placeholder functions to resolve linker errors
void update_game() {
    // Implement game logic updates here later
}

void draw_game() {
    // Implement game drawing code here later
}

