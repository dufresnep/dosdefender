// defender.h - Modified for DJGPP

#pragma once 

//#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pc.h> // DJGPP specific header for hardware access
#include <sys/farptr.h> // For accessing video memory
#include <allegro.h>
#include <stdio.h>

// --- Configuration ---

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200
#define NUM_STARS     100

// --- Types ---

typedef struct {
    int x, y;
} Point;

typedef struct {
    float x, y;
} FloatPoint;

typedef struct {
    int x, y;
    int dx, dy;
    int color;
} Star;

// Declare all needed structures.
struct bullet;
struct particle;
struct ship;
struct powerup;
struct speaker;
struct sample;

// Declare EXTERN global variables (defined in dosdef.c)
extern size_t bullets_max;
extern size_t particles_max;
extern size_t powerups_max;

extern struct bullet *bullets;
extern struct particle *particles;
extern struct ship *ships;
extern struct powerup *powerups;
extern unsigned long score;

// --- Function Prototypes ---

int  init_game();
void update_game();
void draw_game();
void deinit_game();

void clear_screen(int color);
void set_pixel(int x, int y, int color);
int get_pixel(int x, int y);
void draw_line(int x1, int y1, int x2, int y2, int color);
