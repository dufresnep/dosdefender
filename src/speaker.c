// speaker.c
#include "speaker.h"
#include "tone.h" // Include for tone_on and tone_off

// Define AND initialize the 'speaker' variable:
struct speaker speaker = {0, NULL, false, 0}; //Add step initialization

// Define the notes for each sound effect *separately*:
static const struct note fx_explode_notes[] = {
    {62, 1}, {47, 1}, {20, 1}, {96, 1}, {47, 1}, {20, 1},
    {96, 1}, {47, 1}, {20, 1}, {89, 1}, {60, 1}
};
// ... (define notes for other effects similarly) ...
static const struct note fx_hit_notes[] = {
        {120, 3},
        {130, 3},
        {140, 3},
        {150, 3},
        {160, 3}
};

static const struct note fx_boss_notes[] = {
    {110, 15},
    {0,   2},
    {110, 15},
    {0,   2},
    {110, 5},
    {175, 30},
    {0,   2},
    {175, 15},
    {0,   2},
    {175, 15},
    {0,   2},
    {175, 5},
    {110, 30},
};

static const struct note fx_powerup_notes[] = {
    {800, 3},
    {900, 3}
};

static const struct note fx_fire0_notes[] = {
    {200, 1},
    {190, 1},
    {180, 1},
    {170, 1}
};
static const struct note fx_fire1_notes[] = {
        {150, 1},
        {120, 1},
        {100, 1},
        {120, 1},
        {135, 1}
};

static const struct note fx_fire2_notes[] = {
    {300, 1},
    {320, 1},
    {330, 1},
    {335, 1},
    {340, 1}
};

static const struct note fx_fire3_notes[] =
{
    {50,  7},
    {75,  7},
    {100, 7},
    {150, 7},
    {200, 1},
    {250, 1},
    {300, 1},
    {370, 1},
    {360, 1},
    {350, 1},
    {340, 1},
    {330, 1},
    {320, 1},
    {310, 1}
};
static const struct note fx_intro_music_notes[] = {
        {262, 10},
        {247, 10},
        {220, 10},
        {196, 10},
        {247, 10},
        {220, 10},
        {196, 10},
        {247, 10},
        {220, 10},
        {0,   10},
        {110, 20},
};
static const struct note fx_end_music_notes[] = {
    {62, 50},
    {0,  2},
    {62, 50},
    {0,  2},
    {62, 50},
    {0,  2},
    {73, 25},
    {0,  2},
    {65, 20},
    {0,  2},
    {62, 50},
    {0,  2},
    {55, 50},
    {0,  2},
    {62, 100},
};
static const struct note fx_menu_select_notes[] = {
    {800, 2},
    {900, 3},
    {1000, 4},
    {0, 10}
};
static const struct note fx_menu_toggle_notes[] = {
    {600, 2},
    {1000, 1},
    {700, 2}
};

// Now define the sample structures, pointing to the note data:
struct sample fx_explode = { .priority = 10, .length = sizeof(fx_explode_notes) / sizeof(fx_explode_notes[0]), .notes = fx_explode_notes };
struct sample fx_hit     = { .priority = 5,  .length = sizeof(fx_hit_notes) / sizeof(fx_hit_notes[0]),     .notes = fx_hit_notes };
struct sample fx_boss = { .priority = 500,  .length = sizeof(fx_boss_notes) / sizeof(fx_boss_notes[0]),     .notes = fx_boss_notes };
struct sample fx_powerup = { .priority = 50,  .length = sizeof(fx_powerup_notes) / sizeof(fx_powerup_notes[0]),     .notes = fx_powerup_notes };
struct sample fx_fire0 = { .priority = 0,  .length = sizeof(fx_fire0_notes) / sizeof(fx_fire0_notes[0]),     .notes = fx_fire0_notes };
struct sample fx_fire1 = { .priority = -10,  .length = sizeof(fx_fire1_notes) / sizeof(fx_fire1_notes[0]),     .notes = fx_fire1_notes };
struct sample fx_fire2 = { .priority = -5,  .length = sizeof(fx_fire2_notes) / sizeof(fx_fire2_notes[0]),     .notes = fx_fire2_notes };
struct sample fx_fire3 = { .priority = 1,  .length = sizeof(fx_fire3_notes) / sizeof(fx_fire3_notes[0]),     .notes = fx_fire3_notes };
struct sample fx_intro_music = { .priority = 100,  .length = sizeof(fx_intro_music_notes) / sizeof(fx_intro_music_notes[0]),     .notes = fx_intro_music_notes };
struct sample fx_end_music = { .priority = 200, .length = sizeof(fx_end_music_notes) / sizeof(fx_end_music_notes[0]),     .notes = fx_end_music_notes };
struct sample fx_menu_select = { .priority = 55, .length = sizeof(fx_menu_select_notes) / sizeof(fx_menu_select_notes[0]),     .notes = fx_menu_select_notes };
struct sample fx_menu_toggle = { .priority = 50,  .length = sizeof(fx_menu_toggle_notes) / sizeof(fx_menu_toggle_notes[0]),     .notes = fx_menu_toggle_notes };


void speaker_play(struct speaker *speaker, const struct sample *sample) { //Remove const
    if (!speaker->sample || speaker->sample->priority < sample->priority) {
        speaker->sample = sample;
        speaker->index = 0; // Initialize to 0
        speaker->step = 0;  //Initialize to 0
    }
}

void speaker_step(struct speaker *speaker)
{
    if (speaker->sample) {
        if (speaker->step) {
            speaker->step--;
        } else {
            if (speaker->index >= speaker->sample->length) {
                speaker->sample = 0;
                tone_off();
            } else {
                struct note note = speaker->sample->notes[speaker->index];
                if (note.frequency == 0)
                    tone_off();
                else {
                    tone(note.frequency);
                    tone_on();
                }
                speaker->step = note.length;
                speaker->index++; //Increment index
            }
        }
    }
}
