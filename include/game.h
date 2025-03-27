// include/game.h
#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stddef.h> // Add this for size_t
#include "ship.h"
#include "enemy.h"
#include <allegro.h>

// Forward declare structs to avoid full includes if only pointers are needed
struct ship;
struct particle;
struct powerup; // Make sure this matches the actual definition
struct enemy;

// Maximum Bullets
#define MAX_BULLETS 20 // Add this line

// Declare global variables using extern
extern struct ship *ships;
//extern struct bullet bullets[MAX_BULLETS];
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
void init_ship(struct ship *ship);
void clear_screen();
void init_enemy(struct enemy *enemy);

extern volatile int game_running;

#endif
