// dosdef.c (Corrected)
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h> // For abs(), free()
#include "vga.h"
#include "joystick.h"
#include "rand.h"
#include "speaker.h"
#include "alloc.h"
#include "bullet.h"
#include "particle.h"
#include "ship.h"
#include "powerup.h"
#include "time.h"
#include "kb.h"

static size_t bullets_max = 32;
static size_t particles_max = 64;
static size_t ships_max = 12;
static size_t powerups_max = 8;

#define SCALE 1000

// Declare the pointer variables here:
extern struct bullet *bullets;
extern struct particle *particles;
extern struct ship *ships;
extern struct powerup *powerups;
int32_t score = 0;

void bullet_step() //Forward Declaration
{
    bullet_step(bullets, bullets_max, ships, ships_max);
}

#define BACKGROUND         17
#define PLAYER             14
#define BULLET_SPEED       3
#define PARTICLE_MAX_AGE   50
#define MAX_PLAYERS        2

// Inline min and max (if not in a separate header)
static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}



typedef unsigned int tick_t;
typedef void (*ai_t)(int id);
typedef void (*power_t)(int id);

static tick_t ticks;
static unsigned score;
static unsigned best_score;
static struct speaker speaker;

struct ship {
    int32_t x, y, dx, dy;
    tick_t last_fire;
    ai_t ai;
    struct sample *fx_fire;
    uint16_t score;
    uint16_t hp, hp_max;
    uint8_t radius;
    uint8_t fire_delay;
    uint8_t fire_damage;
    uint8_t drop_rate;
    uint8_t color_a, color_b;
    bool is_player;
    union {
        int target_ship;
        struct {
            uint32_t x, y;
        } target_position;
    };
};


struct powerup {
    int32_t x, y;
    tick_t birthtick;
    power_t power;
    bool alive;
    uint8_t color;
};

/*
static struct bullet *bullets;
static size_t bullets_max = 32;

static struct particle *particles;
static size_t particles_max = 64;

static struct ship *ships;
static size_t ships_max = 12;

static struct powerup *powerups;
static size_t powerups_max = 8;
*/

static bool joystick_detected()
{
    struct joystick joystick;
    joystick_read(&joystick);
    return joystick.axis[0] != 0 || joystick.axis[1] != 0;
}

static void burn(int32_t x, int32_t y);
static void ship_draw(int id, bool clear);
static void powerup_random(size_t id);

static bool is_game_over()
{
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (ships[i].is_player && ships[i].hp > 0)
            return false;
    }
    return true;
}

static int ship_fire(int i)
{
    if (ships[i].last_fire + ships[i].fire_delay > ticks)
        return -1;
    ships[i].last_fire = ticks;
    int choice = 0;
    for (size_t i = 0; i < bullets_max; i++) {
        if (!bullets[i].alive) {
            choice = i;
            break;
        } else if (bullets[i].birthtick < bullets[choice].birthtick) {
            choice = i;
        }
    }
    if (bullets[choice].alive)
        bullet_draw(&bullets[choice], true);
    bullets[choice].x = ships[i].x + ships[i].dx / 100;
    bullets[choice].y = ships[i].y + ships[i].dy / 100;
    bullets[choice].dx = ships[i].dx * BULLET_SPEED;
    bullets[choice].dy = ships[i].dy * BULLET_SPEED;
    bullets[choice].color = ships[i].color_b;
    bullets[choice].birthtick = ticks;
    bullets[choice].damage = ships[i].fire_damage;
    bullets[choice].alive = true;
    speaker_play(&speaker, ships[i].fx_fire);
    return choice;
}

static void particle_draw(int i, bool clear)
{
    struct point c = {particles[i].x / SCALE, particles[i].y / SCALE};
    if (clear) {
        vga_pixel(c, BACKGROUND);
    } else {
        int age = ticks - particles[i].birthtick;
        vga_pixel(c, age > PARTICLE_MAX_AGE * 3 / 4
                  ? (randn_max(5) + 24)    // smoke
                  : (randn_max(5) + 40));  // fire
    }
}

static void particle_step(int i)
{
    if (ticks - particles[i].birthtick > PARTICLE_MAX_AGE) {
        particles[i].alive = false;
        particle_draw(i, true);
    } else {
        int speed = 2;
        particles[i].x += randn_max(SCALE * speed) - (SCALE * speed / 2);
        particles[i].y += randn_max(SCALE * speed) - (SCALE * speed / 2);
    }
}

static void burn(int32_t x, int32_t y)
{
    int choice = 0;
    for (size_t i = 0; i < particles_max; i++) {
        if (!particles[i].alive) {
            choice = i;
            break;
        } else if (particles[i].birthtick < particles[choice].birthtick) {
            choice = i;
        }
    }
    if (particles[choice].alive)
        particle_draw(choice, true);
    particles[choice].alive = true;
    particles[choice].x = x;
    particles[choice].y = y;
    particles[choice].birthtick = ticks;
}

static void ship_draw(int id, bool clear)
{
    struct point c = {ships[id].x / SCALE, ships[id].y / SCALE};
    int r = ships[id].radius;
    for (int i = -r + 1; i < r; i++) {
        struct point ha = {ships[id].x / SCALE - i, ships[id].y / SCALE - r};
        struct point hb = {ships[id].x / SCALE - i, ships[id].y / SCALE + r};
        struct point va = {ships[id].x / SCALE - r, ships[id].y / SCALE - i};
        struct point vb = {ships[id].x / SCALE + r, ships[id].y / SCALE - i};
        vga_pixel(ha, clear ? BACKGROUND : ships[id].color_a);
        vga_pixel(va, clear ? BACKGROUND : ships[id].color_a);
        vga_pixel(hb, clear ? BACKGROUND : ships[id].color_a);
        vga_pixel(vb, clear ? BACKGROUND : ships[id].color_a);
    }
    struct point d = {c.x + ships[id].dx / 10, c.y + ships[id].dy / 10};
    if (ships[id].is_player)
        vga_pixel(d, clear ? BACKGROUND : ships[id].color_a);
}

static void ship_step(int i)
{
    ships[i].x += ships[i].dx;
    ships[i].y += ships[i].dy;
    ships[i].dx = (ships[i].dx * 99) / 100;
    ships[i].dy = (ships[i].dy * 99) / 100;
    if (ships[i].hp < ships[i].hp_max / 2) {
        if ((randn_max(ships[i].hp < 1 ? 1 : ships[i].hp) < 10))
            burn(ships[i].x, ships[i].y);
    }
}

static void powerup_draw(int i, bool clear)
{
    int x = powerups[i].x / SCALE;
    int y = powerups[i].y / SCALE;
    uint8_t color;
    tick_t tick = ticks;
    if (clear) {
        color = BACKGROUND;
        tick--;
    } else {
        color = powerups[i].color;
    }
    int size = 0 + (tick / 8) % 3;
    vga_line((struct point){x - size, y},
             (struct point){x + size, y}, color);
    vga_line((struct point){x, y - size},
             (struct point){x, y + size}, color);
}

static void powerup_step(int i)
{
    int px = powerups[i].x / SCALE;
    int py = powerups[i].y / SCALE;
    for (int id = 0; id < MAX_PLAYERS; id++) {
        if (!ships[id].is_player)
            break;
        int sx = ships[id].x / SCALE;
        int sy = ships[id].y / SCALE;
        if (ships[id].hp > 0 &&
            px >= sx - 4 &&
            py >= sy - 4 &&
            px <= sx + 4 &&
            py <= sy + 4) {
            powerups[i].power(id);
            powerups[i].alive = false;
            speaker_play(&speaker, &fx_powerup);
        }
    }
}

static void power_heal(int id)
{
    ships[id].hp = min(ships[id].hp + randn_max(25) + 25, ships[id].hp_max);
}

static void power_resurrect(int id)
{
    ;
    for (int friend = 0; friend < MAX_PLAYERS; friend++) {
        if (ships[friend].is_player && ships[friend].hp == 0) {
            ships[friend].x = ships[id].x;
            ships[friend].y = ships[id].y;
            ships[friend].hp = ships[friend].hp_max / 2;
        }
    }
}

void powerup_random(size_t id) // Use size_t, as in powerup.h
{
    if (ships[id].drop_rate > 0 && randn() % ships[id].drop_rate == 0) {
        int p = powerup_drop(ships[id].x, ships[id].y);
        if (p >= 0) {
            int select = randn() % 100;
            if (select < 25)
                powerups[p].power = POWER_RESURRECT;
            else if (select < 50)
                powerups[p].power = POWER_HEAL;
            else if (select < 70)
                powerups[p].power = POWER_FIRE_DELAY_DOWN;
            else if (select < 90)
                powerups[p].power = POWER_FIRE_DAMAGE_UP;
             else if (select < 95)
                powerups[p].power = POWER_RADIUS_UP;
             else if (select < 99)
                powerups[p].power = POWER_RADIUS_DOWN;
            else
                powerups[p].power = POWER_TELEPORT;

            powerups[p].color = PINK;  // Use a defined color constant
        }
    }
}


static void power_fire_delay_down(int id)
{
    ships[id].fire_delay = max(8, ships[id].fire_delay * 3 / 4);
}

static void power_fire_damage_up(int id)
{
    ships[id].fire_damage = ships[id].fire_damage * 10 / 9;
}

static void power_teleport(int id)
{
    ship_draw(id, true);
    ships[id].x = (randn_max(VGA_PWIDTH - 40) + 20) * SCALE;
    ships[id].y = (randn_max(VGA_PHEIGHT - 40) + 20) * SCALE;
    ships[id].dx = 0;
    ships[id].dy = 0;
}

static void power_radius_up(int id)
{
    ship_draw(id, true);
    ships[id].radius = min(5, ships[id].radius + 1);
}

static void power_radius_down(int id)
{
    ship_draw(id, true);
    ships[id].radius = max(1, ships[id].radius - 1);
}

static void powerup_random(int id)
{
    if (ships[id].drop_rate > 0 && randn_max(ships[id].drop_rate) == 0) {
        int p = powerup_drop(ships[id].x, ships[id].y);
        if (p >= 0) {
            int select = randn_max(100);
            if (select < 5 && ships[1].is_player) {
                powerups[p].power = power_resurrect;
                powerups[p].color = 43;
            } else if (select < 50) {
                powerups[p].power = power_heal;
                powerups[p].color = LIGHT_GREEN;
            } else if (select < 75) {
                powerups[p].power = power_fire_delay_down;
                powerups[p].color = LIGHT_BLUE;
            } else if (select < 95) {
                powerups[p].power = power_fire_damage_up;
                powerups[p].color = LIGHT_RED;
            } else if (select < 97) {
                powerups[p].power = power_radius_up;
                powerups[p].color = PINK; // was LIGHT_MAGENTA; not existing
            } else if (select < 99) {
                powerups[p].power = power_radius_down;
                powerups[p].color = WHITE;
            } else {
                powerups[p].power = power_teleport;
                powerups[p].color = YELLOW;
            }
        }
    }
}

static void print_game_over()
{
    vga_print((struct point){133, 97}, WHITE, "GAME OVER");
}

static void print_exit_help()
{
    vga_print((struct point){76, 160}, LIGHT_GREY,
              "PRESS ANY KEY TO EXIT TO DOS");
    vga_print((struct point){100, 150}, LIGHT_GREY,
              "HOLD FIRE TO RESTART");
}

static void print_title(bool clear)
{
    vga_print((struct point){124, 50}, clear ? BACKGROUND : LIGHT_BLUE,
              "DOS DEFENDER");
}

static void ship_check_bounds(int i)
{
    int32_t xlim = VGA_PWIDTH * SCALE;
    int32_t ylim = VGA_PHEIGHT * SCALE;
    if (ships[i].x < 0 || ships[i].x > xlim ||
        ships[i].y < 0 || ships[i].y > ylim) {
        ships[i].dx = 0;
        ships[i].dy = 0;
        ships[i].hp = 0;
    }
}

int spawn(int hp)
{
    int choice = -1;
    for (size_t i = 1; i < ships_max; i++) {
        if (!ships[i].is_player && ships[i].hp == 0) {
            choice = i;
            break;
        }
    }
    if (choice > -1) {
        ships[choice].is_player = false;
        ships[choice].hp = hp;
        ships[choice].dx = ships[choice].dy = 0;
        if (randn_max(2)) {
            ships[choice].x = randn_max(2) * VGA_PWIDTH * SCALE;
            ships[choice].y = randn_max(VGA_PHEIGHT * SCALE);
        } else {
            ships[choice].x = randn_max(VGA_PWIDTH * SCALE);
            ships[choice].y = randn_max(2) * VGA_PHEIGHT * SCALE;
        }
    }
    return choice;
}

static void ai_player(int i)
{
    if (ships[i].hp > 0) {
        int o = i * 2;
        struct joystick joy;
        struct joystick_config *c = &joystick_config;
        int xrange = 2 * (c->max[o + 0] - c->min[o + 0]);
        int yrange = 2 * (c->max[o + 1] - c->min[o + 1]);
        joystick_read(&joy);
        ships[i].dx += ((joy.axis[o + 0] - c->center[o + 0]) * 100) / xrange;
        ships[i].dy += ((joy.axis[o + 1] - c->center[o + 1]) * 100) / yrange;
        /* mix input into random state */
        seed ^= joy.axis[o + 0] - joy.axis[o + 1];
        if (joy.button[o + 0])
            ship_fire(i);
    }
}

static void ai_dummy(int i)
{
    int dist = SCALE * 25;
    bool no_target = ships[i].target_position.x == 0 ||
                     ships[i].target_position.y == 0;
    bool near_target = abs(ships[i].x - ships[i].target_position.x) < dist &&
                       abs(ships[i].y - ships[i].target_position.y) < dist;
    if (no_target || near_target) {
        ships[i].target_position.x = randn_max(VGA_PWIDTH * SCALE);
        ships[i].target_position.y = randn_max(VGA_PHEIGHT * SCALE);
    }
    int32_t tx = ships[i].target_position.x;
    int32_t ty = ships[i].target_position.y;
    ships[i].dx = (tx - ships[i].x) / 200;
    ships[i].dy = (ty - ships[i].y) / 200;
    if (randn_max(250) == 0)
        ship_fire(i);
}

static void ai_seeker(int i)
{
    int noise = 400;
    int target = ships[i].target_ship;
    if (ships[target].hp == 0 || !ships[target].is_player) {
        ships[i].target_ship = (target + 1) % ships_max;
        if (is_game_over()) {
            ships[i].ai = ai_dummy;
            ships[i].target_position.x = 0;
            ships[i].target_position.y = 0;
        }
    }
    int dx = ships[target].x - ships[i].x;
    int dy = ships[target].y - ships[i].y;
    ships[i].dx = dx / 250 + randn_max(noise) - noise / 2;
    ships[i].dy = dy / 250 + randn_max(noise) - noise / 2;
    ship_fire(i);
}

static bool ending_played = false;

static void clear(int nplayers)
{
    bullets = calloc(bullets_max, sizeof(bullets[0]));
    particles = calloc(particles_max, sizeof(particles[0]));
    ships = calloc(ships_max, sizeof(ships[0]));
    powerups = calloc(powerups_max, sizeof(powerups[0]));

    if (!bullets || !particles || !ships || !powerups) {
        exit(1);
    }


    seed += get_tick();
    for (int i = 0; i < nplayers; i++) {
        ships[i] = (struct ship) {
            .x = VGA_PWIDTH / 2 * SCALE,
            .y = VGA_PHEIGHT / 2 * SCALE,
            .color_a = YELLOW + i,
            .color_b = LIGHT_BLUE,
            .radius = 2,
            .fire_delay = 25,
            .fire_damage = 10,
            .drop_rate = 0,
            .hp = 100,
            .hp_max = 100,
            .ai = ai_player,
            .fx_fire = &fx_fire0,
            .is_player = true
        };
    }
    ticks = 0;
    if (score > best_score)
        best_score = score;
    score = 0;
    ending_played = false;
    speaker.sample = 0;
    speaker_play(&speaker, &fx_intro_music);
    vga_clear(BACKGROUND);
}

static bool ship_exists(uint8_t color)
{
    for (size_t i = 0; i < ships_max; i++)
        if (ships[i].color_a == color)
            return true;
    return false;
}

static int ui_nplayers(void)
{
    int nplayers = 1;
    vga_clear(BACKGROUND);
    print_title(false);
    struct joystick joystick;
    do {
        vga_vsync();
        speaker_step(&speaker);
        vga_print((struct point){130, 90},  nplayers == 1 ? WHITE : DARK_GREY,
                  "ONE PLAYER");
        vga_print((struct point){127, 103}, nplayers == 2 ? WHITE : DARK_GREY,
                  "TWO PLAYERS");
        joystick_read(&joystick);
        int scaled = (joystick.axis[1] - joystick_config.min[1]) * 100
            / (joystick_config.max[1] - joystick_config.min[1]);
        if (scaled > 75) {
            if (nplayers != 2)
                speaker_play(&speaker, &fx_menu_toggle);
            nplayers = 2;
        } else if (scaled < 25) {
            if (nplayers != 1)
                speaker_play(&speaker, &fx_menu_toggle);
            nplayers = 1;
        }
    } while (!joystick.button[0]);
    speaker_play(&speaker, &fx_menu_select);
    do {
        joystick_read(&joystick);
        speaker_step(&speaker);
        vga_vsync();
    } while (joystick.button[0] || speaker.sample != 0);
    return nplayers;
}

static void try_spawn()
{
    int id = spawn(0);
    if (id <= 0)
        return;
    int select = randn_max(100) + ticks / 1000;
    if (select < 65) {
        ships[id].color_a = BROWN;
        ships[id].color_b = LIGHT_RED;
        ships[id].radius = 2;
        ships[id].fire_delay = 100;
        ships[id].fire_damage = 10;
        ships[id].drop_rate = 8;
        ships[id].hp = 10;
        ships[id].hp_max = 10;
        ships[id].score = 100;
        ships[id].ai = ai_seeker;
        ships[id].target_ship = randn_max(MAX_PLAYERS);
        ships[id].fx_fire = &fx_fire1;
    } else if (select < 92) {
        ships[id].color_a = GREEN;
        ships[id].color_b = LIGHT_RED;
        ships[id].radius = 2;
        ships[id].fire_delay = 120;
        ships[id].fire_damage = 10;
        ships[id].drop_rate = 5;
        ships[id].hp = 20;
        ships[id].hp_max = 20;
        ships[id].score = 125;
        ships[id].ai = ai_dummy;
        ships[id].fx_fire = &fx_fire1;
    } else if (select < 93) {
        ships[id].color_a = WHITE;
        ships[id].color_b = LIGHT_RED;
        ships[id].radius = 1;
        ships[id].fire_delay = 20;
        ships[id].fire_damage = 1;
        ships[id].drop_rate = 1;
        ships[id].hp = 1;
        ships[id].hp_max = 1;
        ships[id].score = 500;
        ships[id].ai = ai_seeker;
        ships[id].target_ship = randn_max(MAX_PLAYERS);
        ships[id].fx_fire = &fx_fire1;
    } else if (select < 96) {
        ships[id].color_a = RED;
        ships[id].color_b = LIGHT_GREEN;
        ships[id].radius = 3;
        ships[id].fire_delay = 50;
        ships[id].fire_damage = 25;
        ships[id].drop_rate = 4;
        ships[id].hp = 50;
        ships[id].hp_max = 50;
        ships[id].score = 250;
        ships[id].ai = ai_seeker;
        ships[id].target_ship = randn_max(MAX_PLAYERS);
        ships[id].fx_fire = &fx_fire2;
    } else if (select < 110) {
        ships[id].color_a = PINK; // was non existent LIGHT_MAGENTA;
        ships[id].color_b = LIGHT_CYAN;
        ships[id].radius = 5;
        ships[id].fire_delay = 120;
        ships[id].fire_damage = 50;
        ships[id].drop_rate = 3;
        ships[id].hp = 100;
        ships[id].hp_max = 100;
        ships[id].score = 1000;
        ships[id].ai = ai_seeker;
        ships[id].target_ship = randn_max(MAX_PLAYERS);
        ships[id].fx_fire = &fx_fire3;
    } else if (!ship_exists(LIGHT_GREEN)) {
        ships[id].color_a = LIGHT_GREEN;
        ships[id].color_b = 43;
        ships[id].radius = 8;
        ships[id].fire_delay = 20;
        ships[id].fire_damage = 90;
        ships[id].drop_rate = 4;
        ships[id].hp = 1000;
        ships[id].hp_max = 1000;
        ships[id].score = 10000;
        ships[id].ai = ai_seeker;
        ships[id].target_ship = randn_max(MAX_PLAYERS);
        ships[id].fx_fire = &fx_fire3;
        speaker_play(&speaker, &fx_boss);
    } else {
        ships[id].hp = 0;
    }
}

int main(void)
{
    if (!joystick_detected()) {
        print("A joystick is required to play DOS Defender!$");
        return 1;
    }
    vga_on();
    joystick_calibrate();
    int nplayers = ui_nplayers();

    /* Main Loop */
    clear(nplayers);
    for (;;) {
        speaker_step(&speaker);
        if (randn_max(50) == 0)
            try_spawn();
        if (ticks < 120)
            print_title(false);
        else if (ticks == 120)
            print_title(true);

        if (is_game_over()) {
            struct joystick joystick;
            joystick_read(&joystick);
            if (!ending_played) {
                speaker_play(&speaker, &fx_end_music);
                ending_played = true;
            } else if (!speaker.sample) {
                print_exit_help();
                if (joystick.button[0]) {
                    clear(nplayers);
                    continue;
                }
            }
            print_game_over();
            if (kbhit())
                break;
            if (joystick.button[1]) { // restart early
                clear(nplayers);
                continue;
            }
        }

        vga_vsync();
        for (size_t i = 0; i < particles_max; i++) {
            if (particles[i].alive) {
                particle_draw(i, true);
                particle_step(i);
                if (particles[i].alive)
                    particle_draw(i, false);
            }
        }
        for (size_t i = 0; i < powerups_max; i++) {
            if (powerups[i].alive) {
                powerup_draw(i, true);
                powerup_step(i);
                if (powerups[i].alive)
                    powerup_draw(i, false);
            }
        }
        for (size_t i = 0; i < ships_max; i++) {
            if (ships[i].hp > 0 || ships[i].is_player) {
                ship_draw(i, true);
                ship_step(i);
                ships[i].ai(i);
                if (ships[i].hp > 0)
                    ship_draw(i, false);
            }
        }
        for (int i = 0; i < nplayers; i++)
            ship_check_bounds(i);
        for (size_t i = 0; i < bullets_max; i++) {
            bullet_draw(&bullets[i], true);
            if (bullets[i].alive) {
                bullet_step(i);
                if (bullets[i].alive)
                    bullet_draw(&bullets[i], false);
            }
        }
        ticks++;
    }
    if (score > best_score)
        best_score = score;
    vga_off();
    tone_off();
    print("best score: $");
    printl(best_score);
    return 0;
}
