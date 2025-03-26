#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "../include/game.h"

#include <allegro.h>

#include "../include/defender.h"
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
    printf("Starting the game...\n");
    fflush(stdout);

    allegro_init();
    install_keyboard();
    install_mouse();

    LOCK_FUNCTION(increment_game_time); // Lock the timer interrupt
    install_int_ex(increment_game_time, BPS_TO_TIMER(1000));  // Install the timer to update 1/second

    init_game();

    while (!kbhit()) {  // Use kbhit() for keyboard input
        update_game();
        draw_game();
        rest(10); /* in milliseconds */
    }

    allegro_exit();
    return 0;
}
END_OF_MAIN()
