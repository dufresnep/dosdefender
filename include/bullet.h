//Here is bullet.h. Use that
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h> // for int32_t
#include <stdbool.h>  // bool active
#include <stddef.h> // for size_t

struct point {
    int x;
    int y;
};

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
