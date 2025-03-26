#include <stddef.h> //Adding This
#include <stdio.h> //I forgot
#include <stdlib.h>

#include "../include/powerup.h"
#include "../include/rand.h" //Adding Rand
#include "../include/vga.h"
#include "../include/game.h"

extern int32_t powerups_max;
struct powerup powerups[50];

int powerup_drop(int32_t x, int32_t y) //Enforcing same, also int32_t
{
        // Find an inactive powerup.
        for(size_t i=0; i<powerups_max; i++)
        {
                if(!powerups[i].alive) //enforcing alive
                {
                        powerups[i].x = x;
                        powerups[i].y = y;
                        powerups[i].power = rand() % 2 + 1; // shield or gun
                        powerups[i].birthtick = 1;
                        powerups[i].alive = 1;
                        return 1;
                }
        }

        return 0;
}
