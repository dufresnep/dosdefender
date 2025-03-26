// include/bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>  // For int32_t
#include <allegro.h> //May not need
#include <stdbool.h> // For bool

//Declare before the struct, you need that ENUM before you declare it in the struct
typedef enum {
    bullet_left,
    bullet_right
} bullet_direction;

struct point {
    int x;
    int y;
};

//Declare the structure
struct bullet {
    int32_t x;
    int32_t y;
    bullet_direction dir;
    bool active;
};

//Declare the functions
void bullet_new(struct bullet *b, int32_t x, int32_t y, bullet_direction dir);
void bullet_step(struct bullet *b, size_t id);
void bullet_draw(struct bullet *b);

#endif
