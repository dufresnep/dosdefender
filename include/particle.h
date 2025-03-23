// include/particle.h
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "vga.h"

struct particle {
    int32_t x;
    int32_t y;
    int32_t dx;
    int32_t dy;
    uint8_t color;
    bool alive;
    uint32_t birthtick;
};
