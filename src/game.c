// src/game.c
#include "game.h"
#include "ship.h"

extern struct ship *ships;     // Defined in dosdef.c

bool is_game_over() {

    for (size_t i = 0; i < MAX_PLAYERS; i++) { //Use MAX_PLAYERS

        if (ships[i].is_player && ships[i].hp > 0)
        {
            return false;
        }

    }
    return true;
}
