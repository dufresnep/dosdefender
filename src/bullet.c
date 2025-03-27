#include "../include/bullet.h"
#include <allegro.h>
#include <math.h>
#include <stdio.h>
#include "../include/game.h" // needed for ship

#define BULLET_SPEED 5

struct bullet bullets[MAX_BULLETS];

// Function to initialize a bullet
void init_bullet(struct bullet *bullet) {
    bullet->x = 0;
    bullet->y = 0;
    bullet->dx = 0;
    bullet->dy = 0;
    bullet->damage = 10;
    bullet->color = 15; // White
    bullet->active = false;
}

void update_bullet(struct bullet *bullet, struct ship *player_ship) {
    // Update bullets
    if (true){ //(bullet->active) {
        bullet->x += bullet->dx;
        bullet->y += bullet->dy;

        // Deactivate bullets that are out of bounds
        if (bullet->x < 0 || bullet->x > 319 || bullet->y < 0 || bullet->y > 199) {
            bullet->active = false;
        }

        // Check for collision with player
        float distance = sqrt(pow(player_ship->x - bullet->x, 2) + pow(player_ship->y - bullet->y, 2));
        if (distance < (player_ship->radius + 1)) { // 1 is the bullet radius
            // Collision detected
            bullet->active = false;
            player_ship->hp -= bullet->damage;
            printf("Ship HP: %ld\n", player_ship->hp);

            // Check for game over
            if (player_ship->hp <= 0) {
                extern volatile int game_running;
                printf("Game Over!\n");
                game_running = 0;
            }
        }
    }
}
