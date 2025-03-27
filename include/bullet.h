// include/bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include <stdbool.h>
#include <allegro.h>

#define MAX_BULLETS 20
#define BULLET_SPEED 3

struct bullet {
    int x, y;
    int dx, dy;
    int damage;
    int color;
    bool active;
};

extern struct bullet bullets[MAX_BULLETS];
void init_bullet(struct bullet *bullet);
#endif
