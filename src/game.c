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

// Player's ship
struct ship player_ship; // Add this line

// Function to initialize the ship
void init_ship(struct ship *ship) { // Add this function
    ship->x = 10;
    ship->y = 10;
    ship->dx = 0;
    ship->dy = 0;
    ship->hp = 100;
    ship->hp_max = 100;
    ship->radius = 3;
    ship->color_a = 15; // White
    ship->color_b = 0;  // Black
    ship->is_player = true;
    ship->score = 0;
    ship->fire_damage = 10;
    ship->fire_delay = 20;
    ship->drop_rate = 10;
    ship->last_fire = 0;
    //Other non-graphic initialisation
}

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
    init_ship(&player_ship);
    return 0; // Return 0 if initialization is successful
}

// Placeholder functions to resolve linker errors
void update_game() {
    if (key[KEY_ESC]) {
       stop_game();
    }
    if (key[KEY_LEFT]) {
        player_ship.x--;
    }

    if (key[KEY_RIGHT]) {
        player_ship.x++;
    }
    if (key[KEY_UP]) {
        player_ship.y--;
    }
    if (key[KEY_DOWN]) {
        player_ship.y++;
    }
    if (key[KEY_SPACE]) {
        printf("Space key pressed\n");
        // Add code to fire
    }

    // Delay to avoid CPU hogging
    rest(10);
}

void draw_game() {
    // Clear the screen (crude way, will be replaced by Allegro functions later)
    clear_screen();

    // Draw the ship
    gotoxy(player_ship.x, player_ship.y);
    putchar('*');
}
// Shutdown function (call this from main before exiting)
void shutdown_game() {
    // Remove keyboard interrupt handler
    remove_keyboard();
}

int is_game_running() {
    return game_running;
}

void clear_screen() {
    // This is a very basic way to clear the screen in text mode
    for (int i = 0; i < 25; i++) {
        printf("\n");
    }
    gotoxy(1,1);
}
