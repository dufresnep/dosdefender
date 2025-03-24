// src/dosdef.c
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> //For memset
#include "vga.h"
#include "joystick.h"
#include "rand.h"
#include "speaker.h"
#include "bullet.h"
#include "particle.h"
#include "ship.h"
#include "powerup.h"
#include "time.h"
#include "kb.h"
#include "game.h" //Include game.h
#include "burn.h" //Include burn.h
#include "dosdef.h" // Include its own header!

// Global Variables (Definitions)
size_t bullets_max = 32;
size_t particles_max = 64; //Uncomment
//size_t ships_max = 12;   // Defined as MAX_PLAYERS in ship.h
size_t powerups_max = 8; //Uncomment

struct bullet *bullets;
struct particle *particles;
struct ship *ships;
struct powerup *powerups;
int32_t score = 0; // Use int32_t for consistency
bool running; //Add declaration
extern volatile tick_t ticks; // Defined in time.c

// --- Main Game Logic ---

int main() {
    init_game();  // Initialize the game (sets up VGA, etc.)
    running = true;

    while (running) {
        //vga_vsync();   // Wait for vertical retrace (optional, for smoother animation)

        handle_input();   // Get input from the joystick/keyboard
        update_game();  // Update game state (move bullets, ships, etc.)
        draw_game();    // Draw everything to the screen

        if (kbhit() && getch() == 27) {  // Check for Escape key
            running = false; // Exit the game loop
        }
    }

    vga_off(); // Restore text mode
    return 0; // Return 0 for success
}

// --- Function Definitions ---

void clear(void)
{
    bullets = calloc(bullets_max, sizeof(bullets[0])); //Use calloc
    particles = calloc(particles_max, sizeof(particles[0]));//Use calloc
    ships = calloc(MAX_PLAYERS, sizeof(ships[0]));//Use calloc
    powerups = calloc(powerups_max, sizeof(powerups[0]));//Use calloc
    if (!bullets || !particles || !ships || !powerups)
        exit(1);
    //No need to use memset, because calloc already set memory content to zero.
    ships[0].is_player = true;
    ships[0].hp = 100;
    ships[0].hp_max = 100;
    ships[0].x = 160 * SCALE;
    ships[0].y = 180 * SCALE;
    ships[0].color_a = WHITE;
    ships[0].color_b = LIGHT_RED;
    ships[0].score = 0;
    ships[0].fire_delay = 16;
    ships[0].fire_damage = 1;
    ships[0].radius = 3;
    ships[0].drop_rate = 0; // No powerups
    ships[0].ai = AI_PLAYER; // Use enum value
    ships[0].fx_fire = &fx_fire0;
    score = 0;
    ticks = 0;
    running = true;
}

// --- Function Definitions ---

void init_game(void) {
    vga_on();        // Switch to VGA Mode 13h
    clear();          // Initialize game variables
}

void handle_input(void) {
// TODO
}

void update_game(void) {
     bullet_step(bullets, bullets_max, ships, MAX_PLAYERS);
}

void draw_game(void) {
    for (size_t i = 0; i < bullets_max; i++)
        bullet_draw(&bullets[i], false);

}

void powerup_random(size_t /*id*/) {
}

void try_spawn(void) {}
void print_exit_help() {}
