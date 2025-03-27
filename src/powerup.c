// src/powerup.c
#include "../include/powerup.h"
#include "../include/game.h"  // Need this for the extern 'powerups' pointer and 'powerups_max'
#include <stdlib.h> // For rand()

/*
void powerup_drop(int32_t x, int32_t y) { // Use int32_t
    size_t i; // Use size_t for indexing, consistent with powerups_max
    for(i = 0; i < powerups_max; ++i) { // Use powerups_max
        // We first check for an available powerup
        if(!powerups[i].alive) { // Access elements via the pointer
            // Set it up, and then mark it as alive
            powerups[i].x = x;
            powerups[i].y = y;
            powerups[i].power = rand() % 2 + 1; // shield or gun
            powerups[i].birthtick = 1; // Assuming you'll use game_time later
            powerups[i].alive = true; // Use true for bool
            return; // Found a slot, exit
        }
    }
    // Optional: Handle case where no free slots are found
}
*/

void update_powerup() {
  // Implementation for updating powerups
  // Iterate through the 'powerups' array (using powerups_max)
  // Check 'alive' status, update positions, check lifetime (birthtick vs game_time)
}
