#include "sound.h"

// Back in Black
static const uint16_t bib_noten[] PROGMEM = {
    165, 0, 147, 147, 147, 0, 247, 247, 247, 0,
    330, 294, 247, 220, 196, 165, 0,
    165, 0, 147, 147, 147, 0, 247, 247, 247, 0,
    220, 0, 233, 0, 220, 165
};

static const uint16_t bib_zeit[] PROGMEM = {
    260, 180, 140, 140, 180, 180, 140, 140, 180, 220,
    110, 110, 110, 110, 180, 300, 250,
    260, 180, 140, 140, 180, 180, 140, 140, 180, 220,
    130, 40, 130, 40, 150, 400
};

// Doom: The Only Thing They Fear Is You
static const uint16_t dm_noten[] PROGMEM = {
    82, 82, 0, 82, 82, 165, 0,
    82, 82, 0, 82, 82, 156, 0,
    82, 82, 147, 82, 82, 139, 147
};

static const uint16_t dm_zeit[] PROGMEM = {
    100, 100, 50, 100, 100, 150, 50,
    100, 100, 50, 100, 100, 150, 50,
    100, 100, 120, 100, 100, 120, 200
};

// Star Wars Main Title
static const uint16_t sw_noten[] PROGMEM = {
    440, 440, 440, 349, 523, 440, 349, 523, 440, 0,
    659, 659, 659, 698, 523, 415, 349, 523, 440
};

static const uint16_t sw_zeit[] PROGMEM = {
    350, 350, 350, 250, 120, 350, 250, 120, 700, 150,
    350, 350, 350, 250, 120, 350, 250, 120, 700
};

// Money for Nothing
static const uint16_t mn_noten[] PROGMEM = {
    196, 0, 220, 247, 220, 196, 220, 0,
    294, 294, 247, 0, 220, 0, 196, 165,
    196, 220, 196
};

static const uint16_t mn_zeit[] PROGMEM = {
    180, 60, 180, 180, 180, 180, 260, 100,
    240, 180, 300, 100, 240, 60, 180, 180,
    180, 180, 350
};

static void spiel_lied(uint8_t pin, const uint16_t* noten, const uint16_t* zeit, uint8_t anz)
{
    for (uint8_t i = 0; i < anz; i++)
    {
        uint16_t f = pgm_read_word(&noten[i]);
        uint16_t d = pgm_read_word(&zeit[i]);
        if (f > 0)
            tone(pin, f, d);
        else
            noTone(pin);
        delay(d + 20);
    }
    noTone(pin);
}

void bib_intro(uint8_t pin)
{
    spiel_lied(pin, bib_noten, bib_zeit, sizeof(bib_noten) / sizeof(bib_noten[0]));
}

void doom_intro(uint8_t pin)
{
    spiel_lied(pin, dm_noten, dm_zeit, sizeof(dm_noten) / sizeof(dm_noten[0]));
}

void starwars_intro(uint8_t pin)
{
    spiel_lied(pin, sw_noten, sw_zeit, sizeof(sw_noten) / sizeof(sw_noten[0]));
}

void money_intro(uint8_t pin)
{
    spiel_lied(pin, mn_noten, mn_zeit, sizeof(mn_noten) / sizeof(mn_noten[0]));
}