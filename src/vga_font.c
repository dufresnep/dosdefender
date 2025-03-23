//vga_font.c
#include "vga_font.h"
#include <string.h>

int vga_font_line(int c, int row) {
    if (row < 0 || row > 6)
        return -1;

    // Find character index
    const char* char_ptr = strchr(LINES, c); // Use strchr
    if (char_ptr == NULL)
    {
        return -1; // Char not found
    }

    size_t index = char_ptr - LINES; // Calculate correct index.

    if (index < sizeof(LINES) - 1) //Removed >= 0
    {
      return LETTERS[LINES[index] + row - 0x22];
    }

    return -1;
}
