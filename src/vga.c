// src/vga.c
#include "vga.h"
#include "vga_font.h"
#include <string.h> //memset
#include <sys/farptr.h> //_farpokeb, _farpeekb, _dos_ds
#include <go32.h>     // _dos_ds
#include <dpmi.h>     // __dpmi_int, __dpmi_regs
#include <pc.h>    // inportb, outportb  <-- CORRECTED!
#include <stdio.h>


void vga_clear(uint8_t color) {
    // Fill the entire video memory (320 * 200 bytes) with the given color
    for (int i = 0; i < 320 * 200; i++) {
        _farpokeb(_dos_ds, 0xA0000 + i, color);
    }
}

// src/vga.c
void vga_pixel(struct point p, uint8_t color) {
    //printf("vga_pixel: x=%ld, y=%ld, color=%u\n", (long)p.x, (long)p.y, (unsigned)color); // Debug print
    if (p.x >= 0 && p.x < VGA_PWIDTH && p.y >= 0 && p.y < VGA_PHEIGHT) {
        unsigned long offset = (unsigned long)p.y * VGA_PWIDTH + p.x;
        //printf("  offset: 0x%lX\n", offset); // Debug print
        _farpokeb(_dos_ds, 0xA0000 + offset, color);
    } else {
        printf("  Pixel out of bounds!\n"); // Should not happen with correct Bresenham
    }
}

void vga_line(struct point p1, struct point p2, uint8_t color)
{
    //printf("vga_line: p1=(%ld, %ld), p2=(%ld, %ld), color=%u\n",
    //         (long)p1.x, (long)p1.y, (long)p2.x, (long)p2.y, (unsigned)color); // Debug print

    int dx =  p2.x - p1.x > 0 ? p2.x - p1.x : p1.x - p2.x;
    int dy =  p2.y - p1.y > 0 ? p2.y - p1.y : p1.y - p2.y;
    int sx =  p1.x<p2.x ? 1 : -1;
    int sy =  p1.y<p2.y ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2;
    int e2;
    for(;;){
        //printf("  Loop: p1=(%ld, %ld)\n", (long)p1.x, (long)p1.y); // Debug print
        vga_pixel((struct point){p1.x, p1.y}, color);
        if (p1.x==p2.x && p1.y==p2.y) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; p1.x += sx; }
        if (e2 < dy) { err += dx; p1.y += sy; }
    }
}

void vga_rect(struct point /*p*/, int32_t /*w*/, int32_t /*h*/, uint8_t /*color*/){}//TODO
void vga_crosshair(struct point /*c*/, uint8_t /*color*/){}//TODO
void vga_print(struct point /*p*/, uint8_t /*color*/, const char */*text*/) {}//TODO
void print(const char */*message*/) {} //TODO
void printl(int /*value*/) {} //TODO

void vga_vsync()
{
    // Wait until current scanline is out of visible range.
    while  ((inportb(0x3DA) & 8) != 0); // wait for !retrace
    // Wait until current scanline is in visible range.
    while  ((inportb(0x3DA) & 8) == 0); // wait for retrace
}

/* Switch to VGA mode 13 and set ES. */
void vga_on()
{
    __dpmi_regs regs;  // Structure to hold register values

    // Set the video mode to 0x13 (320x200, 256 colors)
    regs.x.ax = 0x0013;  //  AH=0 (set mode), AL=0x13 (mode 13h)
    __dpmi_int(0x10, &regs); // Call BIOS interrupt 0x10.  Corrected!
}

void vga_off()
{
    __dpmi_regs regs;
    regs.x.ax = 0x0003; //  AH = 0 (set mode), AL = 0x03 (text mode)
    __dpmi_int(0x10, &regs);
}
