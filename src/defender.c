#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "../include/game.h"
#include "../include/defender.h"

#include <allegro.h>

#include "../include/timemy.h"

// Global variables for game time
volatile uint32_t game_time = 0;
volatile uint32_t last_time = 0;

// Function to increment the game time
void increment_game_time() {
    game_time++;
}
END_OF_FUNCTION(increment_game_time);

int main() {
    allegro_init();
    int result = set_gfx_mode(GFX_VGA, 320, 200, 0, 0); // Initialize graphics mode
    printf("set_gfx_mode called\n");
    if (result != 0) {
        allegro_message("Error setting graphics mode: %s\n", allegro_error);
        allegro_exit();
        return 1;
    }


    printf("Starting the game...\n");

    if (init_game() != 0) {
        allegro_message("Error initializing game!\n");
        allegro_exit();
        return 1;
    }

    while (is_game_running()) {
        update_game();
        draw_game();
    }

    shutdown_game();
    printf("Exiting the game...\n");
    allegro_exit();
    return 0;
}
END_OF_MAIN()
