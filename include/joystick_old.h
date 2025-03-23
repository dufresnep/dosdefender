      
#ifndef JOYSTICK_H  // Include guard
#define JOYSTICK_H

#include <stdint.h>
#include <stdbool.h>

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

// Declare joystick_config as extern
extern struct joystick_config joystick_config;

// Function prototypes (declarations)
void joystick_read(struct joystick *joystick);
void joystick_calibrate(); // Add declaration for the calibrate function
#endif

    
//#include "math.h"
//#include "int.h"
