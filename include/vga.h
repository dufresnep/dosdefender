#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stdbool.h>

#define VGA_PWIDTH  320
#define VGA_PHEIGHT 200

enum VGA_COLOR {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GRAY, DARK_GRAY,
    LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA,
    YELLOW, WHITE
};

struct point {
    int x;
    int y;
};

void vga_pixel(struct point p, uint8_t color);
void vga_line(struct point p1, struct point p2, uint8_t color);

#endif
