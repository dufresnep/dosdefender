// src/game.c
#include <stdio.h>
#include <stdlib.h>  // For malloc (if you allocate memory for these)
#include "../include/game.h" // Include the header file!

// Define global variables
struct ship *ships = NULL;    // Initialize to NULL to be safe
struct bullet *bullets = NULL;  // Initialize to NULL to be safe
struct particle *particles = NULL; // Initialize to NULL to be safe
struct powerup *powerups = NULL;   // Initialize to NULL to be safe

size_t bullets_max = 100;
size_t particles_max = 200;
size_t powerups_max = 50;

unsigned long  score = 0;

// Implement your functions here (init_game, update_game, draw_game)
void init_game() {
    // Initialize the game
    // Example: allocate memory for the arrays
    ships = malloc(sizeof(struct ship) * 1); // Assuming 1 ship for now
    bullets = malloc(sizeof(struct bullet) * bullets_max);
    particles = malloc(sizeof(struct particle) * particles_max);
    powerups = malloc(sizeof(struct powerup) * powerups_max);
    if (!ships || !bullets || !particles || !powerups) {
        // Handle memory allocation error
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    //Initialize ships
}

void update_game() {
    // Update the game state
}

void draw_game() {
    // Draw the game on the screen
}
