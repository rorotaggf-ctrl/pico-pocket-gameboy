#include "screensaver.h"

static uint8_t s_art = 0;
static unsigned long s_t = 0;

static int16_t bx = 20;
static int16_t by = 30;
static int8_t b_dx = 2;
static int8_t b_dy = 2;
static uint16_t b_col = ST77XX_RED;

static const uint16_t farben[6] = {
    ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
    ST77XX_YELLOW, ST77XX_MAGENTA, ST77XX_CYAN};
static uint8_t farb_idx = 0;

static int16_t mat_y[16];
static uint8_t mat_sp[16];

static int16_t st_x[40];
static int16_t st_y[40];
static uint8_t st_z[40];
static int16_t alt_x[40];
static int16_t alt_y[40];

static void neu_farb()
{
    farb_idx = (farb_idx + 1) % 6;
    b_col = farben[farb_idx];
}

static void mal_dvd(Adafruit_ST7789 *d, int16_t x, int16_t y, uint16_t c)
{
    d->fillRoundRect(x, y, 54, 24, 6, c);
    d->setTextColor(ST77XX_BLACK);
    d->setTextSize(2);
    d->setCursor(x + 10, y + 5);
    d->print("DVD");
}

static void mal_rr(Adafruit_ST7789 *d, int16_t x, int16_t y, uint16_t c)
{
    d->setTextSize(3);
    d->setTextColor(c);
    d->setCursor(x, y);
    d->print("R");
    d->setCursor(x + 14, y + 8);
    d->print("R");
}

void saver_start(Adafruit_ST7789 *d, uint8_t nr)
{
    s_art = nr;
    d->fillScreen(ST77XX_BLACK);
    s_t = millis();

    if (s_art == 0)
    {
        bx = 40;
        by = 50;
        b_dx = 2;
        b_dy = 2;
        neu_farb();
        mal_dvd(d, bx, by, b_col);
    }
    else if (s_art == 1)
    {
        bx = 50;
        by = 40;
        b_dx = 2;
        b_dy = 2;
        neu_farb();
        mal_rr(d, bx, by, b_col);
    }
    else if (s_art == 2)
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            mat_y[i] = random(-180, 0);
            mat_sp[i] = random(3, 7);
        }
    }
    else
    {
        for (uint8_t i = 0; i < 40; i++)
        {
            st_x[i] = random(-120, 120);
            st_y[i] = random(-120, 120);
            st_z[i] = random(20, 240);
            alt_x[i] = -1;
            alt_y[i] = -1;
        }
    }
}

void saver_tick(Adafruit_ST7789 *d)
{
    if (s_art == 0)
    {
        if (millis() - s_t < 25)
            return;
        s_t = millis();

        d->fillRoundRect(bx, by, 54, 24, 6, ST77XX_BLACK);
        d->fillRect(bx + 8, by + 3, 38, 18, ST77XX_BLACK);

        bx += b_dx;
        by += b_dy;

        uint8_t bump = 0;
        if (bx <= 0 || bx >= 186)
        {
            b_dx = -b_dx;
            bump = 1;
        }
        if (by <= 0 || by >= 216)
        {
            b_dy = -b_dy;
            bump = 1;
        }
        if (bump)
            neu_farb();

        mal_dvd(d, bx, by, b_col);
    }
    else if (s_art == 1)
    {
        if (millis() - s_t < 25)
            return;
        s_t = millis();

        d->fillRect(bx, by, 38, 34, ST77XX_BLACK);

        bx += b_dx;
        by += b_dy;

        uint8_t bump = 0;
        if (bx <= 0 || bx >= 202)
        {
            b_dx = -b_dx;
            bump = 1;
        }
        if (by <= 0 || by >= 206)
        {
            b_dy = -b_dy;
            bump = 1;
        }
        if (bump)
            neu_farb();

        mal_rr(d, bx, by, b_col);
    }
    else if (s_art == 2)
    {
        if (millis() - s_t < 40)
            return;
        s_t = millis();

        for (uint8_t i = 0; i < 16; i++)
        {
            int16_t px = i * 15 + 3;
            int16_t py = mat_y[i];

            if (py >= 0 && py < 232)
            {
                d->fillRect(px, py - 26, 10, 10, ST77XX_BLACK);
                d->setCursor(px, py);
                d->setTextSize(1);
                d->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
                d->print((char)random(33, 90));

                if (py >= 10)
                {
                    d->setCursor(px, py - 10);
                    d->setTextColor(ST77XX_GREEN, ST77XX_BLACK);
                    d->print((char)random(33, 90));
                }
            }

            mat_y[i] += mat_sp[i];
            if (mat_y[i] > 240)
            {
                d->fillRect(px, 200, 10, 40, ST77XX_BLACK);
                mat_y[i] = random(-40, 0);
                mat_sp[i] = random(3, 7);
            }
        }
    }
    else
    {
        if (millis() - s_t < 25)
            return;
        s_t = millis();

        for (uint8_t i = 0; i < 40; i++)
        {
            if (alt_x[i] >= 0 && alt_x[i] < 240 && alt_y[i] >= 0 && alt_y[i] < 240)
                d->drawPixel(alt_x[i], alt_y[i], ST77XX_BLACK);

            if (st_z[i] <= 4)
            {
                st_x[i] = random(-120, 120);
                st_y[i] = random(-120, 120);
                st_z[i] = 240;
                alt_x[i] = -1;
                alt_y[i] = -1;
                continue;
            }
            st_z[i] -= 4;

            int16_t kx = 120 + ((int32_t)st_x[i] * 120) / st_z[i];
            int16_t ky = 120 + ((int32_t)st_y[i] * 120) / st_z[i];

            if (kx < 0 || kx >= 240 || ky < 0 || ky >= 240)
            {
                st_z[i] = 240;
                st_x[i] = random(-120, 120);
                st_y[i] = random(-120, 120);
                alt_x[i] = -1;
                alt_y[i] = -1;
            }
            else
            {
                uint16_t farbe = (st_z[i] < 70) ? ST77XX_WHITE : ((st_z[i] < 150) ? 0x9CD3 : 0x4A49);
                d->drawPixel(kx, ky, farbe);
                alt_x[i] = kx;
                alt_y[i] = ky;
            }
        }
    }
}