// include/bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include <stdbool.h>
#include <allegro.h>

#define MAX_BULLETS 20

struct bullet {
    int x, y;
    int dx, dy;
    int damage;
    int color;
    bool active;
};

extern struct bullet bullets[MAX_BULLETS];

//void bullet_new(struct bullet *b, int32_t x, int32_t y, bullet_direction dir);
void bullet_step(struct bullet *b, size_t id);
void bullet_draw(struct bullet *b);

#endif
