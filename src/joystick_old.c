// joystick.c
#include "joystick.h"
#include <limits.h>
#include "vga.h"        // Include for vga functions
#include "vga_font.h"   // Include if needed
#include "math.h"       // For min/max if not inlined


// Define joystick_config here (in the .c file)
struct joystick_config joystick_config = {
    .min = {UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX},
    .max = {0, 0, 0, 0},
    .center = {0, 0, 0, 0}
};

// Helper functions (inline for efficiency)
static inline uint16_t min(uint16_t a, uint16_t b) {
    return (a < b) ? a : b;
}

static inline uint16_t max(uint16_t a, uint16_t b) {
    return (a > b) ? a : b;
}
// static void joystick_crosshair(struct point c, uint8_t color)
// {
//     vga_line((struct point){c.x - 2, c.y},
//              (struct point){c.x + 2, c.y}, color);
//     vga_line((struct point){c.x, c.y - 2},
//              (struct point){c.x, c.y + 2}, color);
// } // Moved to vga.c


void joystick_read(struct joystick *joystick) {
    uint16_t eax_value;
    uint8_t temp_error; // Temporary 8-bit variable

    asm volatile (
        "mov $0x84, %%ah\n"
        "mov $1, %%dx\n"
        "int $0x15\n"
        "setc %[temp_error]\n"
        //"mov %%ax, %[eax]\n"
        : "=a" (eax_value),
          "=b"(joystick->axis[1]),
          "=c"(joystick->axis[2]),
          "=d"(joystick->axis[3]),
          [temp_error] "=q" (temp_error) // Use "=q" for 8-bit register
        :
        : "memory", "cc"
    );

    joystick->axis[0] = eax_value;
    joystick->error = temp_error; // Assign from the temporary variable

    if (!joystick->error) {
        for (int i = 0; i < 4; i++) {
            joystick_config.min[i] = min(joystick_config.min[i], joystick->axis[i]);
            joystick_config.max[i] = max(joystick_config.max[i], joystick->axis[i]);
        }
    }
}

void joystick_calibrate()
{
    vga_clear(BLUE);
    int32_t scaled[4] = {};
    struct joystick joy;

     // Initialize buttons to false.  CRITICAL for the loop to work correctly.
    for (int i = 0; i < 4; i++) {
        joy.button[i] = false;
    }
    joy.error = false; //Initialize error to false

    do {
        vga_vsync();
        vga_crosshair((struct point){scaled[0], scaled[1]}, BLUE); //Use vga_crosshair
        vga_crosshair((struct point){scaled[2], scaled[3]}, BLUE);
        joystick_read(&joy);

        //Check error before using values
        if(!joy.error) {
            for (int i = 0; i < 4; i++) {
                int32_t scale = joystick_config.max[i] - joystick_config.min[i];
                if (scale != 0) {
                    scaled[i] = joy.axis[i] - joystick_config.min[i];
                    scaled[i] *= (i & 0x01) ? VGA_PHEIGHT : VGA_PWIDTH;
                    scaled[i] /= scale;
                }
            }
            vga_crosshair((struct point){scaled[0], scaled[1]}, WHITE);
            vga_crosshair((struct point){scaled[2], scaled[3]}, YELLOW);
            vga_print((struct point){55, 80}, YELLOW,
                      "MOVE JOYSTICK AROUND ITS FULL RANGE");
            vga_print((struct point){43, 113}, YELLOW,
                      "THEN CENTER JOYSTICK AND PRESS BUTTON A");
            vga_pixel((struct point){VGA_PWIDTH / 2, VGA_PHEIGHT / 2}, BLACK);
        } else {
             vga_print((struct point){55, 80}, RED, "JOYSTICK ERROR!"); //Display error

        }
    } while (!joy.button[0] || joy.error); // Loop until button A and no error

    //Check error before using values
    if(!joy.error)
    {
        for (int i = 0; i < 4; i++)
            joystick_config.center[i] = joy.axis[i];
    }

    vga_clear(LIGHT_BLUE);

    // Initialize buttons to false. CRITICAL for the loop to work correctly.
    for(int i=0; i<4; ++i) {
        joy.button[i] = false;
    }
    do {
        joystick_read(&joy);
    } while (joy.button[0]);  // Loop while button A is pressed (release)
}
