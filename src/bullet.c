// src/bullet.c
#include "bullet.h"
#include "speaker.h"
#include "ship.h"
#include "vga.h"
#include "rand.h"
#include "burn.h"
#include "game.h"
#include "powerup.h"
#include "dosdef.h"

extern struct ship *ships;
//extern size_t ships_max;       //Defined in dosdef.c, use MAX_PLAYERS
extern int32_t score;
extern struct speaker speaker;
extern struct sample fx_explode;
extern struct sample fx_hit;

struct bullet bullet_create(int32_t x, int32_t y, int32_t dx, int32_t dy, uint8_t color) {
    struct bullet b;
    b.x = x;
    b.y = y;
    b.dx = dx;
    b.dy = dy;
    b.color = color;
    b.alive = true;
    b.birthtick = 0;
    b.damage = 0;
    return b; // Add return statement
}

void bullet_update(struct bullet *b) {
    // ... (implementation of bullet_update, if any) ...
  //TO BE IMPLEMENTED
}
void bullet_draw(struct bullet *b, bool clear) {
	 //struct point c = {b->x / SCALE, b->y / SCALE}; //Commented because unused
	 //if(clear)
		//  vga_pixel(c, BLACK);
    //TO BE IMPLEMENTED
}

bool bullet_in_ship(struct bullet *b, struct ship *s)
{
    //TO BE IMPLEMENTED
    return false; //Temporary, for compilation
}

void bullet_step(struct bullet *bullets, size_t num_bullets, struct ship *ships, size_t num_ships)
{
    for (size_t i = 0; i < num_bullets; i++) {
        if(bullets[i].alive) {
            bullets[i].x += bullets[i].dx;
            bullets[i].y += bullets[i].dy;

            if (bullets[i].x < 0 || bullets[i].x > VGA_PWIDTH * SCALE ||
                bullets[i].y < 0)
                bullets[i].alive = false;

            for (size_t id = 0; id < MAX_PLAYERS; id++) { //Use MAX_PLAYERS
                if (ships[id].hp > 0 && ships[id].color_b != bullets[i].color) {
                    if (bullet_in_ship(&bullets[i], &ships[id])) {
                        bullets[i].alive = false;
                        if (ships[id].hp >= bullets[i].damage)
                            ships[id].hp -= bullets[i].damage;
                        else
                            ships[id].hp = 0;

                        burn(ships[id].x, ships[id].y);
                        ship_draw(id, true); // Corrected call
                        if (!is_game_over())
                            score += ships[id].score;

                        powerup_random(id); // You have powerup_random definition.
                        if (ships[id].hp == 0)
                            speaker_play(&speaker, &fx_explode);
                        else
                            speaker_play(&speaker, &fx_hit);

                    }

                }
            }
        }
    }
}
