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

// Last pressed direction
int desired_dx = 0; // Add this line
int desired_dy = 0; // Add this line
#define MAX_VELOCITY 5
#define ACCELERATION 1

// Function to initialize the ship
void init_ship(struct ship *ship) { // Add this function
    ship->x = 160;
    ship->y = 100;
    ship->dx = 2;
    ship->dy = 2;
    ship->hp = 100;
    ship->hp_max = 100;
    ship->radius = 5;
    ship->color_a = makecol(255, 255, 255); // White
    ship->color_b = makecol(0, 0, 0);  // Black
    ship->is_player = true;
    ship->score = 0;
    ship->fire_damage = 10;
    ship->fire_delay = 20;
    ship->drop_rate = 10;
    ship->last_fire = 0;
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
    // Check for key presses
    // Check for ESC key
    if (key[KEY_ESC]) {
        stop_game();
    }

    // Update ship velocity based on arrow keys
    if (key[KEY_LEFT]) {
        player_ship.dx -= ACCELERATION;
         if (player_ship.dx < -MAX_VELOCITY)  player_ship.dx = -MAX_VELOCITY;
    }

    if (key[KEY_RIGHT]) {
        player_ship.dx += ACCELERATION;
         if (player_ship.dx > MAX_VELOCITY)  player_ship.dx = MAX_VELOCITY;
    }

    if (key[KEY_UP]) {
        player_ship.dy -= ACCELERATION;
         if (player_ship.dy < -MAX_VELOCITY)  player_ship.dy = -MAX_VELOCITY;
    }

    if (key[KEY_DOWN]) {
        player_ship.dy += ACCELERATION;
         if (player_ship.dy > MAX_VELOCITY)  player_ship.dy = MAX_VELOCITY;
    }

    // Update ship position based on velocity
    player_ship.x += player_ship.dx;
    player_ship.y += player_ship.dy;

    if (key[KEY_SPACE]) {
        printf("Space key pressed\n");
        // Add code to fire
    }

    // Keep ship within bounds (example)
    if (player_ship.x < 0) player_ship.x = 0;
    if (player_ship.x > 319) player_ship.x = 319;
    if (player_ship.y < 0) player_ship.y = 0;
    if (player_ship.y > 199) player_ship.y = 199;

    // Delay to avoid CPU hogging
    rest(10);
}

void draw_game() {
    // Clear the screen
    clear_to_color(screen, makecol(0, 0, 0)); // Black

    // Draw the ship as a circle
    circlefill(screen, player_ship.x, player_ship.y, player_ship.radius, player_ship.color_a);
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
    // This is now useless
}
