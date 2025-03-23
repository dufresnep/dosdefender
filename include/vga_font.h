// include/vga_font.h
#pragma once

#include "vga.h" // Only vga.h is needed

static const char LINES[]   = "BCDEIKOPQRSTUVYZ\\_`";
static const char LETTERS[] =
    "B\x06" "C\x06" "D\x06" "E\x05" "I\x03" "K\x06" "O\x06" "P\x05"
    "Q\x06" "R\x06" "S\x06" "T\x05" "U\x06" "V\x06" "Y\x05" "Z\x05"
    "\\\x05" "_\x05" "`\x04"
    "BCEILMNOPQRSTUVZ\\`"
    "CDELNORSUZ\\`"
    "BCDEIKLOPQRSTUVYZ\\`"
    "BCDEIKNOPQRSTUVYZ\\`"
    "BCDEHIKLOPQRSTVYZ\\`"
    "BDEHKMOPQRSVYZ\\`"
    "BCDEFGHIJKLMNOPQRSTUVYZ\\`";

int vga_font_line(int c, int row);
