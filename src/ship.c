// src/ship.c
#include "ship.h"
#include "vga.h"

extern struct ship *ships; // Declare ships as extern
//extern size_t ships_max; // Declare as extern

void ship_draw(int id, bool clear)
{
    struct point c = {ships[id].x / SCALE, ships[id].y / SCALE}; // Use ships[id]
    int r = ships[id].radius;

    struct point ha[] = {
        {c.x - 2 * r, c.y - r}, {c.x - 2 * r, c.y + r}, {c.x + 2 * r, c.y}};
    struct point hb[] = {
        {c.x - 2 * r, c.y + r}, {c.x + 2 * r, c.y}, {c.x - 2 * r, c.y - r}};

    for (int i = 0; i < 3; i++) {
        vga_pixel(ha[i], clear ? BLACK : ships[id].color_a); // Use BLACK
        vga_pixel(hb[i], clear ? BLACK : ships[id].color_b); // Use BLACK
    }
}
