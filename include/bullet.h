//Here is bullet.h. Use that
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // Add this

enum bullet_direction {
    bullet_left,
    bullet_right
};

struct bullet {
    int32_t x;
    int32_t y;
    enum bullet_direction dir; // <-- Check if exists
    bool active; // <--- Check if exists, if the names does not match, the computer will complain
};

void bullet_new(struct bullet *b, int32_t x, int32_t y, enum bullet_direction dir);
void bullet_step(struct bullet *b, size_t id);
void bullet_draw(struct bullet *b);

#endif
