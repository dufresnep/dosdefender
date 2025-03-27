#ifndef BULLET_H
#define BULLET_H


#include <stdbool.h>
#include "enemy.h"
#include <allegro.h>

#define MAX_BULLETS 20  // Define MAX_BULLETS here

struct bullet {
    int x, y;
    int dx, dy;
    int32_t damage;
    int color;
    bool active;
};

struct ship;
struct enemy;

extern struct bullet bullets[MAX_BULLETS]; // Add this line
void init_bullet(struct bullet *bullet);
void update_bullet(struct bullet *bullet, struct ship *player_ship, struct enemy enemies[], int max_enemies);

#endif
