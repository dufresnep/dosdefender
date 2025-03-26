// include/ship.h
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // for size_t
#include "vga.h"
#include "timemy.h"


#define MAX_PLAYERS 12
#define SCALE 1000

// Define the AI types (using an enum is a good way to do this)
typedef enum {
    AI_NONE,      // No AI
    AI_PLAYER,    // Player-controlled
    AI_DUMMY,     // Simple AI
    AI_SEEKER,    // Another AI type
    // ... add more AI types as needed ...
} ai_t;

struct ship {
    int32_t x;
    int32_t y;
    int32_t dx;
    int32_t dy;
    int32_t hp;      // Current hit points
    int32_t hp_max;  // Maximum hit points
    int32_t radius;
    uint8_t color_a;
    uint8_t color_b;
    bool is_player;
    int32_t score;
    int32_t fire_damage;
    int32_t fire_delay;
    int32_t drop_rate;
    struct point target_position; // Example: Target position for AI
    int target_ship;
    tick_t last_fire;    // Use tick_t
    ai_t ai;              // Use ai_t
    struct sample *fx_fire; // Pointer to sample
};

extern size_t ships_max;

void ship_draw(int id, bool clear);
void ship_step(int i);
void ai_player(int i);
void ai_dummy(int i);
void ai_seeker(int i);
// ... other ship-related function prototypes ...
