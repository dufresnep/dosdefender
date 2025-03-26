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


// Function to set the game_running flag to 0 on key press (e.g., ESC)
//Interrupt routine.
void stop_game(void) {
    game_running = 0;
}

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

    install_keyboard();
    return 0; // Return 0 if initialization is successful
}

// Placeholder functions to resolve linker errors
void update_game() {
    if (keypressed()){
        int key_code = readkey() & 0xFF; // removes the scan code
        printf("Key pressed: %d\n", key_code);
        if (key_code == 27){
           stop_game();
        }
    }
    rest(10);
}

void draw_game() {
    // Implement game drawing code here later
    // For now, just print a message
}
// Shutdown function (call this from main before exiting)
void shutdown_game() {
    // Remove keyboard interrupt handler
    remove_keyboard();
}

int is_game_running() {
    return game_running;
}

