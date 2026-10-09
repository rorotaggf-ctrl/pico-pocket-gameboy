#include "flappy.h"
#include <Preferences.h>

static const uint8_t f_a = 27;
static const uint8_t f_b = 14;
static const uint8_t f_pieps = 13;

static int16_t by;
static int8_t vy;
static int16_t rx;
static int16_t rh;
static uint8_t luecke;
static uint16_t f_score;
static uint16_t f_hs;
static unsigned long ft;
static bool ftot;
static Preferences p_flp;

static void neu_rohr()
{
    rx = 240;
    rh = random(25, 130);
    luecke = (f_score < 25) ? (70 - f_score) : 45;
}

void flappy_setup(Adafruit_ST7789 *d)
{
    pinMode(f_a, INPUT_PULLUP);
    pinMode(f_b, INPUT_PULLUP);
    pinMode(f_pieps, OUTPUT);

    p_flp.begin("game", false);
    f_hs = p_flp.getUShort("flp_hs", 0);

    d->fillScreen(ST77XX_BLACK);
    by = 120;
    vy = 0;
    f_score = 0;
    ftot = false;
    neu_rohr();
}

int flappy_loop(Adafruit_ST7789 *d)
{
    if (digitalRead(f_b) == LOW)
        return 1;

    if (ftot)
    {
        if (digitalRead(f_a) == LOW)
            flappy_setup(d);
        return 0;
    }

    if (digitalRead(f_a) == LOW)
    {
        vy = -4;
        tone(f_pieps, 600, 20);
    }

    if (millis() - ft > 35)
    {
        ft = millis();
        d->fillRect(40, by, 10, 10, ST77XX_BLACK);
        d->fillRect(rx, 0, 16, rh, ST77XX_BLACK);
        d->fillRect(rx, rh + luecke, 16, 240 - (rh + luecke), ST77XX_BLACK);

        vy += 1;
        by += vy;

        int8_t speed = (f_score < 10) ? 4 : ((f_score < 25) ? 5 : 6);
        rx -= speed;

        if (rx < -16)
        {
            f_score++;
            neu_rohr();
            tone(f_pieps, 900, 30);
        }

        if (by < 0 || by > 230 || (rx <= 50 && rx >= 24 && (by < rh || by + 10 > rh + luecke)))
        {
            ftot = true;
            tone(f_pieps, 150, 400);

            if (f_score > f_hs)
            {
                f_hs = f_score;
                p_flp.putUShort("flp_hs", f_hs);
            }

            d->setCursor(55, 95);
            d->setTextColor(ST77XX_RED);
            d->setTextSize(2);
            d->print("GAME OVER");

            d->setCursor(65, 130);
            d->setTextColor(ST77XX_WHITE);
            d->print("PKT: ");
            d->print(f_score);

            d->setCursor(65, 160);
            d->setTextColor(ST77XX_YELLOW);
            d->print("TOP: ");
            d->print(f_hs);

            return 0;
        }

        d->fillRect(rx, 0, 16, rh, ST77XX_GREEN);
        d->fillRect(rx, rh + luecke, 16, 240 - (rh + luecke), ST77XX_GREEN);
        d->fillRect(40, by, 10, 10, ST77XX_YELLOW);
    }
    return 0;
}