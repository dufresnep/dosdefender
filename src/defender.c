/*src/defender.c*/
#include <stdio.h>
#include "defender.h"
#include <allegro.h>
#include "timemy.h"
#include "game.h" 

// Define global variables
struct ship *ships;
struct bullet *bullets;
struct particle *particles;
struct powerup *powerups;

size_t bullets_max = 100;
size_t particles_max = 200;
size_t powerups_max = 50;

int32_t score = 0;

/* A timer to count milliseconds */
volatile int game_time = 0;
void increment_game_time() {
    game_time++;
}
END_OF_FUNCTION(increment_game_time);

int main() {
    printf("Starting the game...\n");

    allegro_init();
    LOCK_FUNCTION(increment_game_time);
    install_int_ex(increment_game_time, BPS_TO_TIMER(1000));
    set_color_depth(8);
/*
    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) {
        allegro_message("Error setting graphics mode: %s\n", allegro_error);
        allegro_exit();
        return 1;
    }
*/
    install_keyboard();
    install_mouse();

    init_game();

    while (!keypressed()) {
        update_game();
        draw_game();
        rest(10); /* in miliseconds */
    }

    allegro_exit();
    printf("Exiting the game...\n");
    return 0;
}
END_OF_MAIN()
