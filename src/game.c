#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>
#include <time.h>
#include "../include/bullet.h" // Add this line

// Flag to control the game loop
volatile int game_running = 1;

// Player's ship
struct ship player_ship;

// Maximum ship velocity
#define MAX_VELOCITY 2

// Bullet speed
#define BULLET_SPEED 3

// Enemy variables
//#define MAX_ENEMIES 10
struct enemy enemies[MAX_ENEMIES];

// Function to initialize the ship
void init_ship(struct ship *ship) {
    ship->x = 160; // Center of the screen
    ship->y = 100; // Center of the screen
    ship->dx = 0; // Initial horizontal speed
    ship->dy = 0; // Initial vertical speed
    ship->hp = 100;
    ship->hp_max = 100;
    ship->radius = 5; // Increased radius for better visibility
    ship->color_a = makecol(255, 255, 255); // White
    ship->color_b = makecol(0, 0, 0);  // Black
    ship->is_player = true;
    ship->score = 0;
    ship->fire_damage = 10;
    ship->fire_delay = 20;
    ship->drop_rate = 10;
    ship->last_fire = 0;
}

// Function to initialize an enemy
void init_enemy(struct enemy *enemy) {
    enemy->x = rand() % 320; // Random x position
    enemy->y = rand() % 200; // Random y position
    enemy->dx = (rand() % 3) - 1; // Random horizontal direction (-1, 0, or 1)
    enemy->dy = (rand() % 3) - 1; // Random vertical direction (-1, 0, or 1)
    enemy->hp = 50;
    enemy->max_hp = 50;
    enemy->radius = 4;
    enemy->color = makecol(100, 40, 0); // Brown
    enemy->fire_delay = 50;
    enemy->last_fire = 0;
    enemy->active = true;
}

// Function to set the game_running flag to 0 on key press (e.g., ESC)
void stop_game() {
    game_running = 0;
}

// Placeholder functions to resolve linker errors
void update_game() {
    if (key[KEY_1]) {
        printf("Key '1' is pressed!\n");
        for (int i = 0; i < MAX_BULLETS; i++) {
                    printf("bullet active=%d  ",bullets[i].active);
                    //printf("bullet.x=%d\n",bullets[i].x);
                    //printf("bullet.y=%d\n",bullets[i].y);
                    printf("bullet.dx=%d  ",bullets[i].dx);
                    printf("bullet.dy=%d  ",bullets[i].dy);
                    //printf("bullet.color=%d\n",bullets[i].color);
        }
    }

    // Check for key presses
    // Check for ESC key
    if (key[KEY_ESC]) {
        stop_game();
    }

    // Update ship velocity based on arrow keys
    if (key[KEY_LEFT]) {
        player_ship.dx = -MAX_VELOCITY;
    }
    if (key[KEY_RIGHT]) {
        player_ship.dx = MAX_VELOCITY;
    }
    if (key[KEY_UP]) {
        player_ship.dy = -MAX_VELOCITY;
    }
    if (key[KEY_DOWN]) {
        player_ship.dy = MAX_VELOCITY;
    }

    // Update ship position based on velocity
    player_ship.x += player_ship.dx;
    player_ship.y += player_ship.dy;

    // Player shooting
    if (key[KEY_SPACE]) {
        // Check fire delay
        if (true){ //(player_ship.last_fire + player_ship.fire_delay < time(NULL)) {
            // Find an inactive bullet
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    // Fire bullet
                    bullets[i].active = true;
                    bullets[i].x = player_ship.x + player_ship.dx * 4;
                    bullets[i].y = player_ship.y + player_ship.dy * 4;
                    bullets[i].dx = player_ship.dx * 1.5; // Set bullet direction to ship's direction
                    bullets[i].dy = player_ship.dy * 1.5 ; // Add bullet speed, and reverse
                    bullets[i].color = makecol(255, 0, 0); // Red
                    bullets[i].damage = 15; // Hope to destroy with 1 shot
                    player_ship.last_fire = time(NULL);
                    break; // Only fire one bullet at a time
                }
            }
        }
    }

    // Keep ship within bounds (example)
    if (player_ship.x < 0) player_ship.x = 0;
    if (player_ship.x > 319) player_ship.x = 319;
    if (player_ship.y < 0) player_ship.y = 0;
    if (player_ship.y > 199) player_ship.y = 199;

    // Update enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            enemies[i].x += enemies[i].dx;
            enemies[i].y += enemies[i].dy;

            // Keep enemies within bounds
            if (enemies[i].x < 0 || enemies[i].x > 319) {
                enemies[i].dx = -enemies[i].dx; // Reverse horizontal direction
            }
            if (enemies[i].y < 0 || enemies[i].y > 199) {
                enemies[i].dy = -enemies[i].dy; // Reverse vertical direction
            }
            // Enemy shooting
            if (rand() % 100 < 2) {
                // Find an inactive bullet
                for (int j = 0; j < MAX_BULLETS; j++) {
                    if (!bullets[j].active) {
                        // Calculate the angle to the player
                        float angle = atan2(player_ship.y - enemies[i].y, player_ship.x - enemies[i].x);

                        // Fire bullet
                        bullets[j].active = true;
                        bullets[j].x = enemies[i].x + enemies[i].dx*4; // if bullet at enemy position, bullet would hit enemy
                        bullets[j].y = enemies[i].y + enemies[i].dy*4;
                        bullets[j].dx = cos(angle) * 5;
                        bullets[j].dy = sin(angle) * 5;
                        bullets[j].color = 15;
                        bullets[j].damage = 10;
                        break; // Only fire one bullet at a time
                    }
                }
            }
        }
    }

// Update bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        update_bullet(&bullets[i], &player_ship, enemies, MAX_ENEMIES);
    }

    // Delay to avoid CPU hogging
    rest(10);
}

void draw_game() {
    // Clear the screen
    clear_to_color(screen, makecol(0, 0, 0)); // Black

    // Draw the ship as a circle
    circlefill(screen, player_ship.x, player_ship.y, player_ship.radius, player_ship.color_a);

    // Draw enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            // Calculate HP percentage
            float hp_percentage = (float)enemies[i].hp / enemies[i].max_hp;

            // Interpolate color between brown and red
            int red = 100 + (int)(155 * (1 - hp_percentage)); // Interpolate red component
            int green = 40;
            int blue = 0;
            int color = makecol(red, green, blue);

            circlefill(screen, enemies[i].x, enemies[i].y, enemies[i].radius, color);
        }
    }

    // Draw bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            circlefill(screen, bullets[i].x, bullets[i].y, 1, bullets[i].color); // Draw bullet as a pixel
        }
    }
}

int init_game() {
    // Initialize Allegro's keyboard
    install_keyboard();

    // Initialize the ship
    init_ship(&player_ship);

    // Initialize random seed
    srand(time(NULL));

    // Initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        init_enemy(&enemies[i]);
    }

    return 0;
}

void shutdown_game() {
    // Remove Allegro's keyboard handler (not strictly necessary, but good practice)
    remove_keyboard();
}

int is_game_running() {
    return game_running;
}

void clear_screen() {
    // This is a very basic way to clear the screen in text mode
    // This is now useless
}
