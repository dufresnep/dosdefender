// src/ship.c
#include <stdio.h> // For printf (debugging)
#include "../include/ship.h"
#include "../include/vga.h"
#include "../include/game.h"

extern struct ship *ships; // Declare ships as extern

void ship_draw(int id, bool clear)
{
    //printf("Entering ship_draw(id: %d, clear: %d)\n", id, clear); // REMOVE THIS for final version
    struct point c = {ships[id].x / SCALE, ships[id].y / SCALE}; // Use ships[id]
    int r = ships[id].radius;
    struct point p1, p2, p3;
    uint8_t color;

    if (clear) {
        color = BLACK;
    } else {
        color = ships[id].color_a;
    }
    // Define the three points of the triangle
     p1.x = c.x;
     p1.y = c.y - 2 * r;  // Top point

     p2.x = c.x - 2 * r;
     p2.y = c.y + r;     // Bottom-left point

     p3.x = c.x + 2 * r;
     p3.y = c.y + r;     // Bottom-right point

     // Draw the three lines of the triangle
     //printf("Drawing lines...\n"); // REMOVE THIS for final version
     vga_line(p1, p2, color);
     vga_line(p2, p3, color);
     vga_line(p3, p1, color);
     //printf("Exiting ship_draw()\n"); // REMOVE THIS for final version
}

void ship_step(int /*i*/) {} //TODO

void ai_player(int /*i*/) {} //TODO

void ai_dummy(int /*i*/) {} //TODO

void ai_seeker(int /*i*/) {} //TODO
