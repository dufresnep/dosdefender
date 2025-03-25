// src/dosdef.c
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> //For memset
#include <conio.h>  //For kbhit and getch
#include <stdio.h>  // Add this for printf
#include <dpmi.h>   // Add this for __dpmi_regs and __dpmi_int
#include "vga.h"
#include "joystick.h"
#include "rand.h"
#include "speaker.h"
#include "bullet.h"
#include "particle.h"
#include "ship.h"
#include "powerup.h"
#include "time.h"
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
// --- Function Prototypes (Declarations) ---
//    (Make sure these match the definitions later)

// Functions from dosdef.c itself:
// Moved to dosdef.h

// --- Main Game Logic ---

int main() {
    init_game();  // Initialize the game (sets up VGA, etc.)
    running = true;

    while (running) {
        vga_vsync();   // Wait for vertical retrace (optional, for smoother animation)

        handle_input();   // Get input from the joystick/keyboard
        update_game();  // Update game state (move bullets, ships, etc.)
        draw_game();    // Draw everything to the screen

        if (kbhit() && getch() == 27) {  // Check for Escape key
            running = false; // Exit the game loop
        }
    }

    vga_off(); // Restore text mode
    vga_clear(BLACK); //Clear screen
    return 0;
}

// --- Function Definitions ---

void clear()
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
void init_game(void) {
     vga_on();  // Switch to VGA Mode 13h
     clear();   // Initialize game variables
}

void handle_input(void) {
    // TODO: Implement input handling (joystick, keyboard)
}

void update_game(void) {
    // TODO: Implement game logic (moving ships, particles, etc.)
     bullet_step(bullets, bullets_max, ships, MAX_PLAYERS);

}

void draw_game(void) {
  //  ship_draw(0, false);
    vga_line((struct point){10, 20}, (struct point){40, 20}, RED); // Horizontal line
    vga_line((struct point){20, 30}, (struct point){20, 60}, GREEN); // Vertical line
    vga_line((struct point){30, 40}, (struct point){70, 80}, BLUE);   // Diagonal line
}

void powerup_random(size_t /*id*/) // Use size_t, as in powerup.h
{
//...
}

void try_spawn(void) {} //TODO
void print_exit_help(){} //TODO
