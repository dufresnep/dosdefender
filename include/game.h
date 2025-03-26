// include/game.h
#ifndef GAME_H
#define GAME_H

#include <stdint.h>  // For int32_t

// Define the structures (if they aren't already)
struct ship {
    // Ship data members
};

struct bullet {
    // Bullet data members
};

struct particle {
    // Particle data members
};

struct powerup {
    // Powerup data members
};

// Declare the global variables using extern
extern struct ship *ships;
extern struct bullet *bullets;
extern struct particle *particles;
extern struct powerup *powerups;

extern size_t bullets_max;
extern size_t particles_max;
extern size_t powerups_max;

extern unsigned long score;

// Function prototypes (existing ones)
void init_game();
void update_game();
void draw_game();

#endif
