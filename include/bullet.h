// include/bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include <stdbool.h>
#include "../include/common.h" // Include common.h for struct point

// REMOVE the definition of struct point from here:
/*
struct point {
    int x;
    int y;
};
*/

typedef enum {
    bullet_left,
    bullet_right
} bullet_direction;

struct bullet {
    int32_t x;
    int32_t y;
    bullet_direction dir;
    bool active;
};

void bullet_new(struct bullet *b, int32_t x, int32_t y, bullet_direction dir);
void bullet_step(struct bullet *b, size_t id);
void bullet_draw(struct bullet *b);

#endif
