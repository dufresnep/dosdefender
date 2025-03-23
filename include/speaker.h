// speaker.h
#pragma once

#include <stddef.h> // For size_t
#include <stdbool.h>

#define SAMPLE_RATE 22050

struct note {
    unsigned frequency;
    unsigned length;
};

struct sample {
    int priority;
    size_t length;
    const struct note *notes;
};

struct speaker {
    size_t index;
    const struct sample *sample;
    bool on;
    int step;  // Add step member
};

extern struct speaker speaker;
extern struct sample fx_explode;
extern struct sample fx_hit;
extern struct sample fx_boss;
extern struct sample fx_powerup;
extern struct sample fx_fire0;
extern struct sample fx_fire1;
extern struct sample fx_fire2;
extern struct sample fx_fire3;
extern struct sample fx_intro_music;
extern struct sample fx_end_music;
extern struct sample fx_menu_select;
extern struct sample fx_menu_toggle;

void speaker_play(struct speaker *speaker, const struct sample *sample); //Remove const
void speaker_step(struct speaker *speaker);
