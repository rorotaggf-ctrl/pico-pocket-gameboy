#include "wolf.h"
#include <math.h>

static const uint8_t oben = 32;
static const uint8_t unten = 33;
static const uint8_t links = 25;
static const uint8_t rechts = 26;
static const uint8_t a = 27;
static const uint8_t b = 14;
static const uint8_t pieps = 13;

static float px = 2.5;
static float py = 2.5;
static float pa = 0.0;
static uint8_t waffen_anim = 0;

static uint8_t karte[16][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 2, 0, 0, 1, 0, 1, 2, 1, 0, 1, 1, 0, 1},
    {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 2, 2, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 2, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 2, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

static void male_waffe(Adafruit_ST7789 *d)
{
    if (waffen_anim > 0)
    {
        d->fillTriangle(120, 190, 100, 240, 140, 240, ST77XX_YELLOW);
        d->fillCircle(120, 190, 8, ST77XX_WHITE);
        waffen_anim--;
    }
    else
    {
        d->fillRect(114, 205, 12, 35, 0x4208);
        d->fillRect(116, 195, 8, 10, 0x7BEF);
    }
    d->drawFastHLine(116, 120, 9, ST77XX_GREEN);
    d->drawFastVLine(120, 116, 9, ST77XX_GREEN);
}

void wolf_setup(Adafruit_ST7789 *d)
{
    pinMode(oben, INPUT_PULLUP);
    pinMode(unten, INPUT_PULLUP);
    pinMode(links, INPUT_PULLUP);
    pinMode(rechts, INPUT_PULLUP);
    pinMode(a, INPUT_PULLUP);
    pinMode(b, INPUT_PULLUP);
    pinMode(pieps, OUTPUT);

    px = 2.5;
    py = 2.5;
    pa = 0.0;
    waffen_anim = 0;

    d->fillRect(0, 0, 240, 120, 0x2104);
    d->fillRect(0, 120, 240, 120, 0x4208);
    male_waffe(d);
}

int wolf_loop(Adafruit_ST7789 *d)
{
    if (digitalRead(b) == LOW)
        return 1;

    bool render = false;

    if (digitalRead(links) == LOW)
    {
        pa -= 0.08;
        render = true;
    }
    if (digitalRead(rechts) == LOW)
    {
        pa += 0.08;
        render = true;
    }

    float dx = cos(pa) * 0.12;
    float dy = sin(pa) * 0.12;

    if (digitalRead(oben) == LOW)
    {
        if (karte[(uint8_t)(py)][(uint8_t)(px + dx * 1.5)] == 0)
            px += dx;
        if (karte[(uint8_t)(py + dy * 1.5)][(uint8_t)(px)] == 0)
            py += dy;
        render = true;
    }
    if (digitalRead(unten) == LOW)
    {
        if (karte[(uint8_t)(py)][(uint8_t)(px - dx * 1.5)] == 0)
            px -= dx;
        if (karte[(uint8_t)(py - dy * 1.5)][(uint8_t)(px)] == 0)
            py -= dy;
        render = true;
    }

    if (digitalRead(a) == LOW && waffen_anim == 0)
    {
        waffen_anim = 3;
        tone(pieps, 1800, 30);
        delay(10);
        tone(pieps, 300, 60);

        float rcos = cos(pa);
        float rsin = sin(pa);
        float d_s = 0.0;
        while (d_s < 8.0)
        {
            d_s += 0.2;
            int16_t sx = (int16_t)(px + rcos * d_s);
            int16_t sy = (int16_t)(py + rsin * d_s);
            if (sx >= 0 && sx < 16 && sy >= 0 && sy < 16)
            {
                if (karte[sy][sx] == 2)
                {
                    karte[sy][sx] = 0;
                    tone(pieps, 120, 150);
                    break;
                }
                else if (karte[sy][sx] == 1)
                {
                    break;
                }
            }
        }
        render = true;
    }

    if (waffen_anim > 0)
        render = true;

    if (!render)
        return 0;

    for (uint8_t i = 0; i < 60; i++)
    {
        float strahl_a = pa - 0.45 + (i * 0.9 / 60.0);
        float rcos = cos(strahl_a);
        float rsin = sin(strahl_a);

        float dist = 0.0;
        uint8_t wand = 0;

        while (dist < 14.0)
        {
            dist += 0.06;
            int16_t kx = (int16_t)(px + rcos * dist);
            int16_t ky = (int16_t)(py + rsin * dist);

            if (kx >= 0 && kx < 16 && ky >= 0 && ky < 16)
            {
                if (karte[ky][kx] > 0)
                {
                    wand = karte[ky][kx];
                    break;
                }
            }
        }

        dist *= cos(strahl_a - pa);

        int16_t h = (int16_t)(180.0 / dist);
        if (h > 240)
            h = 240;

        int16_t start_y = 120 - (h / 2);
        int16_t end_y = 120 + (h / 2);

        uint16_t col;
        if (wand == 2)
            col = (dist < 4.0) ? 0x07E0 : ((dist < 8.0) ? 0x04A0 : 0x0280);
        else
            col = (dist < 4.0) ? 0xF800 : ((dist < 8.0) ? 0xB800 : 0x7800);

        uint8_t sp_x = i * 4;

        d->fillRect(sp_x, 0, 4, start_y, 0x2104);
        d->fillRect(sp_x, start_y, 4, h, col);
        d->fillRect(sp_x, end_y, 4, 240 - end_y, 0x4208);
    }

    male_waffe(d);
    return 0;
}