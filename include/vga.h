// include/vga.h
#pragma once

#include <stdint.h>
#include <stddef.h>

struct point {
    int32_t x;
    int32_t y;
};

void vga_clear(uint8_t color);
void vga_pixel(struct point p, uint8_t color);
void vga_line(struct point p1, struct point p2, uint8_t color);
void vga_rect(struct point p, int32_t w, int32_t h, uint8_t color);
void vga_print(struct point p, uint8_t color, const char *text);
void vga_vsync();
void vga_crosshair(struct point c, uint8_t color);
void vga_on();
void vga_off();
void print(const char *message);
void printl(int value);

#define VGA_PWIDTH 320
#define VGA_PHEIGHT 200
#define SCALE 1000

#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHT_GREY    7
#define DARK_GREY     8
#define LIGHT_BLUE    9
#define LIGHT_GREEN  10
#define LIGHT_CYAN   11
#define LIGHT_RED    12
#define PINK         13
#define YELLOW       14
#define WHITE        15
