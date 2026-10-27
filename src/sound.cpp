#include "sound.h"

static const uint16_t bib_noten[] PROGMEM = {
    165, 0, 147, 147, 147, 0, 247, 247, 247, 0,
    330, 294, 247, 220, 196, 165, 0,
    165, 0, 147, 147, 147, 0, 247, 247, 247, 0,
    220, 0, 233, 0, 220, 165};

static const uint16_t bib_zeit[] PROGMEM = {
    260, 180, 140, 140, 180, 180, 140, 140, 180, 220,
    110, 110, 110, 110, 180, 300, 250,
    260, 180, 140, 140, 180, 180, 140, 140, 180, 220,
    130, 40, 130, 40, 150, 400};

void bib_intro(uint8_t pin)
{
    uint8_t anz = sizeof(bib_noten) / sizeof(bib_noten[0]);
    for (uint8_t i = 0; i < anz; i++)
    {
        uint16_t f = pgm_read_word(&bib_noten[i]);
        uint16_t d = pgm_read_word(&bib_zeit[i]);
        if (f > 0)
            tone(pin, f, d);
        else
            noTone(pin);
        delay(d + 20);
    }
    noTone(pin);
}