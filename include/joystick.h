// include/joystick.h
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "include/vga.h"

struct joystick {
    uint16_t axis[4];
    bool button[4];
    bool error;
};

struct joystick_config {
    uint16_t min[4];
    uint16_t max[4];
    uint16_t center[4];
};

extern struct joystick_config joystick_config;

void joystick_read(struct joystick *joystick);
void joystick_calibrate();
