// include/game.h
#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stddef.h> // Add this for size_t
#include "ship.h"
#include <allegro.h>

// Forward declare structs to avoid full includes if only pointers are needed
struct ship;
struct bullet;
struct particle;
struct powerup; // Make sure this matches the actual definition

// Declare global variables using extern
extern struct ship *ships;
extern struct bullet *bullets;
extern struct particle *particles;
extern struct powerup *powerups; // Keep as pointer

extern size_t bullets_max;
extern size_t particles_max;
extern size_t powerups_max; // Keep as size_t

extern unsigned long score; // Use unsigned long as decided before
extern BITMAP *screen;

// Function prototypes
int  init_game();
void update_game();
void draw_game();
void shutdown_game();
int is_game_running();
void clear_screen();

extern volatile int game_running;

#endif
