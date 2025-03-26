// src/bullet.c
#include "../include/bullet.h"

//You should not need to declare it any more!
//void bullet_new(struct bullet *b, int32_t x, int32_t y, bullet_direction dir);
//void bullet_step(struct bullet *b, size_t id);
//void bullet_draw(struct bullet *b);
//We can confirm the functions work, by declaring them here first!

void bullet_new(struct bullet *b, int32_t x, int32_t y, bullet_direction dir) {
    b->x = x;
    b->y = y;
    b->dir = dir;
    b->active = 1;
}

void bullet_step(struct bullet *b, size_t id) {
    if(!b->active)
        return;

    if(b->dir == bullet_left) {  // Added curly braces
        b->x -= 5;
    } else {                   // Added curly braces
        b->x += 5;
    }

    if (b->x < 0 || b->x > 319) {
        b->active = 0;
    }
}

void bullet_draw(struct bullet *b) {
    if(!b->active)
        return;

    struct point p;
    p.x = b->x;
    p.y = b->y;
    // Now you would draw the thing
}
