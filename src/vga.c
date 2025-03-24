// vga.c
#include "vga.h"
#include "vga_font.h"
#include <dpmi.h>

void vga_clear(uint8_t color) {
    // ... (your vga_clear implementation) ...
    asm volatile ("mov   %%al, %%ah\n"
                  "mov   $0, %%di\n"
                  "push  %%ax\n"
                  "shl   $16, %%eax\n"
                  "pop   %%ax\n"
                  "mov   $16000, %%cx\n"
                  "rep\n"
                  "stosl\n"
                  : /* no outputs */
                  : "a"(color)
                  : "cx", "di");
}

void vga_pixel(volatile struct point p, uint8_t color)
{
    if (p.x >= 0 && p.x < VGA_PWIDTH && p.y >= 0 && p.y < VGA_PHEIGHT)
        asm volatile ("imul  $320, %%bx\n"
                      "add   %%ax, %%bx\n"
                      "mov   %%cl, %%es:(%%bx)\n"
                      : /* no outputs */
                      : "a"(p.x), "b"(p.y), "c"(color)
                      : "dx");
}

void vga_line(struct point p1, struct point p2, uint8_t color){
    int dx =  p2.x - p1.x > 0 ? p2.x - p1.x : p1.x - p2.x;
    int dy =  p2.y - p1.y > 0 ? p2.y - p1.y : p1.y - p2.y;
    int sx =  p1.x<p2.x ? 1 : -1;
    int sy =  p1.y<p2.y ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    for(;;){
        vga_pixel((struct point){p1.x, p1.y}, color);
        if (p1.x==p2.x && p1.y==p2.y) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; p1.x += sx; }
        if (e2 < dy) { err += dx; p1.y += sy; }
    }
}

void vga_rect(struct point p, int32_t w, int32_t h, uint8_t color){
 for(int i=0; i<w; i++)
    {
        for(int j=0; j<h; j++)
        {
            vga_pixel((struct point){p.x + i, p.y +j}, color);
        }
    }
}

void vga_crosshair(struct point c, uint8_t color)
{
    vga_line((struct point){c.x - 2, c.y},
             (struct point){c.x + 2, c.y}, color);
    vga_line((struct point){c.x, c.y - 2},
             (struct point){c.x, c.y + 2}, color);
}
void vga_print(struct point p, uint8_t color, const char *text)
{
    for (int i = 0; text[i] != '\0'; i++) {
        for (int row = 0; row < 7; row++) {
            int line = vga_font_line(text[i], row);
            if (line >= 0) {
                if (line & 0x10) vga_pixel((struct point){p.x - 3, p.y + row}, color);
                if (line & 0x08) vga_pixel((struct point){p.x - 2, p.y + row}, color);
                if (line & 0x04) vga_pixel((struct point){p.x - 1, p.y + row}, color);
                if (line & 0x02) vga_pixel((struct point){p.x + 0, p.y + row}, color);
                if (line & 0x01) vga_pixel((struct point){p.x + 1, p.y + row}, color);
            }
        }
        p.x += 6;
    }
}

// src/vga.c
void vga_on() {
    __dpmi_regs regs;  // Structure to hold register values

    // Set the video mode to 0x13 (320x200, 256 colors)
    regs.x.ax = 0x0013;  //  AH=0 (set mode), AL=0x13 (mode 13h)
    __dpmi_int(0x10, &regs); // Call BIOS interrupt 0x10
}

void vga_off()
{
    asm volatile ("mov   $0x0003, %%ax\n"
                  "int   $0x10\n"
                  "mov   $0xA000, %%dx\n"
                  "mov   %%dx, %%es\n"
                  : /* no outputs */
                  : /* no inputs */
                  : "ax", "dx");
}
void print(const char *message)
{
     for(int i=0; message[i] != '\0'; i++){
        asm volatile(
            "mov $0x0E, %%ah\n"
            "mov %0, %%al\n"
            "int $0x10\n"
            :
            :"r"(message[i])
            :"ax"
        );
    }
}
void printl(int value)
{
    char buffer[12];
    int i = 0;

    if (value == 0) {
        buffer[i++] = '0';
    } else {
        if (value < 0) {
            print("-");
            value = -value;
        }
        while (value > 0) {
            buffer[i++] = (value % 10) + '0';
            value /= 10;
        }
        i--;
    }

    while(i >= 0)
    {
        print(&buffer[i]);
        i--;
    }
}

void vga_vsync()
{
  //Wait until current scanline is out of visible range.
  asm volatile (
    "vsync_wait_out:\n"
    "mov $0x3DA, %%dx\n"
    "in %%dx, %%al\n"
    "test $0x08, %%al\n"  //Bit 3 is vertical retrace. 0: not in, 1: in
    "jz vsync_wait_out\n"  //Wait until not in retrace.

    "vsync_wait_in:\n"      //Must not be in retrace now
    "mov $0x3DA, %%dx\n"
    "in %%dx, %%al\n"
    "test $0x08, %%al\n"
    "jnz vsync_wait_in\n"  //Loop until *in* retrace.
    :
    :
    :"ax", "dx"
  );
}
