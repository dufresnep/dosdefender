// src/joystick.c
#include <stdbool.h>
#include <limits.h>

#include "../include/joystick.h"
#include "../include/vga.h"
#include "../include/vga_font.h"

struct joystick_config joystick_config = {
    .min = {UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX},
    .max = {0, 0, 0, 0},
    .center = {0, 0, 0, 0}
};

static inline uint16_t min(uint16_t a, uint16_t b) {
    return (a < b) ? a : b;
}

static inline uint16_t max(uint16_t a, uint16_t b) {
    return (a > b) ? a : b;
}
void joystick_read(struct joystick *joystick) {
    uint16_t eax_value;
    uint8_t  temp_error;
    uint16_t temp_b;
    uint16_t temp_c;
    uint16_t temp_d;


    asm volatile (
        "mov $0x84, %%ah\n"
        "mov $1, %%dx\n"
        "int $0x15\n"
        "setc %[temp_error]\n"
        : "=a" (eax_value),  // AX is special - keep "=a" for the return value
          "=r"(temp_b),     // Use "=r" and temporaries
          "=r"(temp_c),
          "=r"(temp_d),
          [temp_error] "=q" (temp_error)
        :
        : "memory", "cc"
    );

    joystick->axis[0] = eax_value;
    joystick->axis[1] = temp_b;
    joystick->axis[2] = temp_c;
    joystick->axis[3] = temp_d;
    joystick->error = temp_error;

    if (!joystick->error) {
        for (int i = 0; i < 4; i++) {
            joystick_config.min[i] = min(joystick_config.min[i], joystick->axis[i]);
            joystick_config.max[i] = max(joystick_config.max[i], joystick->axis[i]);
        }
    }
}

void joystick_calibrate()
{
 //...
}
