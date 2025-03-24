// include/dosdef.h
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Declare all needed structures.
struct bullet;
struct particle;
struct ship;
struct powerup;
struct speaker;
struct sample;

// Declare EXTERN global variables (defined in dosdef.c)
extern size_t bullets_max;
extern size_t particles_max;
extern size_t powerups_max;

extern struct bullet *bullets;
extern struct particle *particles;
extern struct ship *ships;
extern struct powerup *powerups;
extern int32_t score;

// Function prototypes for functions DEFINED in dosdef.c
void clear(void);
void init_game(void); // If you have this function
void handle_input(void); // If you have this function
void update_game(void);  // If you have this function
void draw_game(void);    // If you have this function
void powerup_random(size_t id);
void try_spawn(void); // Corrected
void print_exit_help();
//void bullet_step(struct bullet *bullets, size_t num_bullets, struct ship *ships, size_t num_ships); // Defined in bullet.c
