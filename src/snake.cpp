#include "snake.h"
#include <Preferences.h>

static const uint8_t oben = 32;
static const uint8_t unten = 33;
static const uint8_t links = 25;
static const uint8_t rechts = 26;
static const uint8_t btn_a = 27;
static const uint8_t btn_b = 14;
static const uint8_t pieps = 13;

static uint8_t sx[100];
static uint8_t sy[100];
static uint8_t slen = 3;
static uint8_t dir = 1;
static uint8_t ax = 120;
static uint8_t ay = 120;
static uint16_t s_hs = 0;
static unsigned long st = 0;
static bool stot = false;
static Preferences p_snk;

static void neu_apfel()
{
    ax = (random(2, 22)) * 10;
    ay = (random(2, 22)) * 10;
}

void snake_setup(Adafruit_ST7789 *d)
{
    pinMode(oben, INPUT_PULLUP);
    pinMode(unten, INPUT_PULLUP);
    pinMode(links, INPUT_PULLUP);
    pinMode(rechts, INPUT_PULLUP);
    pinMode(btn_a, INPUT_PULLUP);
    pinMode(btn_b, INPUT_PULLUP);
    pinMode(pieps, OUTPUT);

    p_snk.begin("game", false);
    s_hs = p_snk.getUShort("snk_hs", 0);

    d->fillScreen(ST77XX_BLACK);
    d->drawRect(10, 10, 220, 220, ST77XX_WHITE);
    slen = 3;
    dir = 1;
    sx[0] = 60;
    sy[0] = 60;
    sx[1] = 50;
    sy[1] = 60;
    sx[2] = 40;
    sy[2] = 60;
    stot = false;
    neu_apfel();
    d->fillRect(ax, ay, 8, 8, ST77XX_RED);
}

int snake_loop(Adafruit_ST7789 *d)
{
    if (digitalRead(btn_b) == LOW)
        return 1;

    if (stot)
    {
        if (digitalRead(btn_a) == LOW)
            snake_setup(d);
        return 0;
    }

    if (digitalRead(oben) == LOW && dir != 2)
        dir = 0;
    if (digitalRead(rechts) == LOW && dir != 3)
        dir = 1;
    if (digitalRead(unten) == LOW && dir != 0)
        dir = 2;
    if (digitalRead(links) == LOW && dir != 1)
        dir = 3;

    uint16_t interval = (slen < 40) ? (120 - (slen * 2)) : 45;

    if (millis() - st > interval)
    {
        st = millis();
        int16_t nx = sx[0];
        int16_t ny = sy[0];

        if (dir == 0)
            ny -= 10;
        if (dir == 1)
            nx += 10;
        if (dir == 2)
            ny += 10;
        if (dir == 3)
            nx -= 10;

        if (nx < 10 || nx >= 230 || ny < 10 || ny >= 230)
        {
            stot = true;
            tone(pieps, 150, 400);

            uint16_t pkt = slen - 3;
            if (pkt > s_hs)
            {
                s_hs = pkt;
                p_snk.putUShort("snk_hs", s_hs);
            }

            d->setCursor(75, 95);
            d->setTextColor(ST77XX_RED);
            d->setTextSize(2);
            d->print("TOT");

            d->setCursor(65, 130);
            d->setTextColor(ST77XX_WHITE);
            d->print("PKT: ");
            d->print(pkt);

            d->setCursor(65, 160);
            d->setTextColor(ST77XX_YELLOW);
            d->print("TOP: ");
            d->print(s_hs);

            return 0;
        }

        for (uint8_t i = 0; i < slen; i++)
        {
            if (sx[i] == nx && sy[i] == ny)
            {
                stot = true;
                tone(pieps, 150, 400);

                uint16_t pkt = slen - 3;
                if (pkt > s_hs)
                {
                    s_hs = pkt;
                    p_snk.putUShort("snk_hs", s_hs);
                }

                d->setCursor(75, 95);
                d->setTextColor(ST77XX_RED);
                d->setTextSize(2);
                d->print("TOT");

                d->setCursor(65, 130);
                d->setTextColor(ST77XX_WHITE);
                d->print("PKT: ");
                d->print(pkt);

                d->setCursor(65, 160);
                d->setTextColor(ST77XX_YELLOW);
                d->print("TOP: ");
                d->print(s_hs);

                return 0;
            }
        }

        if (nx == ax && ny == ay)
        {
            if (slen < 99)
                slen++;
            tone(pieps, 800, 40);
            neu_apfel();
            d->fillRect(ax, ay, 8, 8, ST77XX_RED);
        }
        else
        {
            d->fillRect(sx[slen - 1], sy[slen - 1], 8, 8, ST77XX_BLACK);
        }

        for (uint8_t i = slen - 1; i > 0; i--)
        {
            sx[i] = sx[i - 1];
            sy[i] = sy[i - 1];
        }
        sx[0] = nx;
        sy[0] = ny;
        d->fillRect(sx[0], sy[0], 8, 8, ST77XX_GREEN);
    }
    return 0;
}