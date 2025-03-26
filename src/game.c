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
#include <allegro.h>

// Define global variables
struct ship *ships = NULL;
struct bullet *bullets = NULL;
struct particle *particles = NULL;
struct powerup *powerups = NULL;   // Define as pointer, initialize to NULL

size_t bullets_max = 100;
size_t particles_max = 200;
size_t powerups_max = 50;          // Define size here

unsigned long score = 0;

volatile int game_running = 1;

void  stop_game(){
    game_running = 0;
}
END_OF_FUNCTION(stop_game);

int init_game() {
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

    // Install keyboard interrupt handler
    LOCK_FUNCTION(stop_game);
    install_int_ex(stop_game, BPS_TO_TIMER(100)); // Call stop_game function at about 100 times per second

    return 0; // Return 0 if initialization is successful
}

// Placeholder functions to resolve linker errors
void update_game() {
    // Implement game logic updates here later
    // For now, just print a message and check for ESC key
    printf("Updating game...\n");

    if (keypressed()) {
        if (key[KEY_ESC]) {
            stop_game();
        }
    }

    // Delay to avoid CPU hogging (adjust as needed)
    rest(10); // Milliseconds
}

void draw_game() {
    // Implement game drawing code here later
    // For now, just print a message
    printf("Drawing game...\n");
}

// Shutdown function (call this from main before exiting)
void shutdown_game() {
    // Remove keyboard interrupt handler
    remove_int(stop_game);
}

int is_game_running() {
    return game_running;
}
