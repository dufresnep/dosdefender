// include/game.h
#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stddef.h> // Add this for size_t

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

// Function prototypes
void init_game();
void update_game();
void draw_game();

#endif
