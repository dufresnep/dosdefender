#include <allegro.h>
#include "../include/bullet.h"
#include <math.h>
#include "../include/game.h" // Needed for ship and enemy
#include <stdio.h> // printf debugging

#define BULLET_SPEED 5

//This is were data happens for each bullet
struct bullet bullets[MAX_BULLETS];

// Function to initialize a bullet
void init_bullet(struct bullet *bullet) {
    bullet->x = 0;
    bullet->y = 0;
    bullet->dx = 0;
    bullet->dy = 0;
    bullet->damage = 10;
    bullet->color = makecol(0,255,0); //Red? - TO CHECK
    bullet->active = false;
}

//This function update all math of one unique bullet
void update_bullet(struct bullet *bullet, struct ship *player_ship, struct enemy enemies[], int max_enemies) {
    // Update bullets
    if (bullet->active) {
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
            //if(player_ship->hp<0) //Is it unsigned?
            player_ship->hp -= bullet->damage;
           // extern volatile int game_running; //Why again?
            printf("Ship HP: %ld\n", player_ship->hp);
            // Check for game over
            if (player_ship->hp <= 0) {
                extern volatile int game_running; //WTF?

                printf("Game Over!\n");
                game_running = 0;
            }
        }
// Check for collision with enemies
         for (int i = 0; i < max_enemies; i++) {
            if (enemies[i].active) {
                float distance = sqrt(pow(enemies[i].x - bullet->x, 2) + pow(enemies[i].y - bullet->y, 2));
                if (distance < (enemies[i].radius + 1)) { // 1 is the bullet radius
                    // Collision detected
                    bullet->active = false;
                    enemies[i].hp -= bullet->damage;
                    printf("Enemy HP: %d\n", enemies[i].hp);

                    // Check for enemy death
                    if (enemies[i].hp <= 0) {
                        enemies[i].active = false;
                        printf("Enemy destroyed!\n");
                    }
                    break; // Exit enemy loop after collision
                }
            }
        }
    }
}
