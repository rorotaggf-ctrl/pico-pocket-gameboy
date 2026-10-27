#include "pong.h"

static const uint8_t oben = 32;
static const uint8_t unten = 33;
static const uint8_t a = 27;
static const uint8_t b = 14;
static const uint8_t pieps = 13;

static int16_t x;
static int16_t y;
static int8_t dx;
static int8_t dy;
static int16_t sy;
static int16_t by;
static uint8_t p1;
static uint8_t p2;
static uint8_t stufe;
static bool menue;
static unsigned long t;

static void mal_diff(Adafruit_ST7789 *d)
{
    d->fillScreen(ST77XX_BLACK);
    d->setTextSize(2);
    d->setCursor(55, 40);
    d->setTextColor(ST77XX_WHITE);
    d->print("LEVEL");

    d->setTextColor(stufe == 0 ? ST77XX_GREEN : ST77XX_WHITE);
    d->setCursor(55, 90);
    d->print("1. LEICHT");

    d->setTextColor(stufe == 1 ? ST77XX_GREEN : ST77XX_WHITE);
    d->setCursor(55, 130);
    d->print("2. MITTEL");

    d->setTextColor(stufe == 2 ? ST77XX_GREEN : ST77XX_WHITE);
    d->setCursor(55, 170);
    d->print("3. SCHWER");
}

static void starte_match(Adafruit_ST7789 *d)
{
    d->fillScreen(ST77XX_BLACK);
    d->drawFastVLine(120, 0, 240, 0x4208);
    x = 118;
    y = 118;
    dx = (stufe == 0) ? 2 : ((stufe == 1) ? 3 : 4);
    dy = 2;
    sy = 100;
    by = 100;
    p1 = 0;
    p2 = 0;
    menue = false;
    t = millis();
}

void pong_setup(Adafruit_ST7789 *d)
{
    pinMode(oben, INPUT_PULLUP);
    pinMode(unten, INPUT_PULLUP);
    pinMode(a, INPUT_PULLUP);
    pinMode(b, INPUT_PULLUP);
    pinMode(pieps, OUTPUT);

    stufe = 0;
    menue = true;
    mal_diff(d);
}

int pong_loop(Adafruit_ST7789 *d)
{
    if (digitalRead(b) == LOW)
        return 1;

    if (menue)
    {
        if (digitalRead(oben) == LOW)
        {
            stufe = (stufe > 0) ? stufe - 1 : 2;
            mal_diff(d);
            delay(170);
        }
        if (digitalRead(unten) == LOW)
        {
            stufe = (stufe < 2) ? stufe + 1 : 0;
            mal_diff(d);
            delay(170);
        }
        if (digitalRead(a) == LOW)
        {
            starte_match(d);
            delay(180);
        }
        return 0;
    }

    if (digitalRead(oben) == LOW && sy > 4)
    {
        d->fillRect(10, sy, 6, 36, ST77XX_BLACK);
        sy -= 4;
        d->fillRect(10, sy, 6, 36, ST77XX_WHITE);
    }
    if (digitalRead(unten) == LOW && sy < 200)
    {
        d->fillRect(10, sy, 6, 36, ST77XX_BLACK);
        sy += 4;
        d->fillRect(10, sy, 6, 36, ST77XX_WHITE);
    }

    if (millis() - t > 25)
    {
        t = millis();

        d->fillRect(x, y, 6, 6, ST77XX_BLACK);

        d->fillRect(224, by, 6, 36, ST77XX_BLACK);
        int8_t bot_speed = (stufe == 0) ? 2 : ((stufe == 1) ? 3 : 4);
        if (by + 18 < y && by < 200)
            by += bot_speed;
        else if (by + 18 > y && by > 4)
            by -= bot_speed;
        d->fillRect(224, by, 6, 36, ST77XX_WHITE);

        x += dx;
        y += dy;

        if (y <= 2 || y >= 232)
        {
            dy = -dy;
            tone(pieps, 450, 15);
        }

        if (x <= 16 && x >= 10 && y + 6 >= sy && y <= sy + 36)
        {
            dx = (stufe == 0) ? 2 : ((stufe == 1) ? 3 : 4);
            dy = (y + 3 - (sy + 18)) / 5;
            if (dy == 0)
                dy = 1;
            tone(pieps, 750, 20);
        }

        if (x >= 218 && x <= 224 && y + 6 >= by && y <= by + 36)
        {
            dx = (stufe == 0) ? -2 : ((stufe == 1) ? -3 : -4);
            tone(pieps, 650, 20);
        }

        if (x < 2)
        {
            p2++;
            tone(pieps, 150, 200);
            x = 118;
            y = 118;
            dx = (stufe == 0) ? 2 : ((stufe == 1) ? 3 : 4);
        }
        else if (x > 234)
        {
            p1++;
            tone(pieps, 1100, 100);
            x = 118;
            y = 118;
            dx = (stufe == 0) ? -2 : ((stufe == 1) ? -3 : -4);
        }

        d->fillRect(x, y, 6, 6, ST77XX_WHITE);
        d->fillRect(10, sy, 6, 36, ST77XX_WHITE);
        d->drawFastVLine(120, 0, 240, 0x4208);

        d->setCursor(85, 10);
        d->setTextColor(ST77XX_WHITE, ST77XX_BLACK);
        d->setTextSize(2);
        d->print(p1);
        d->setCursor(145, 10);
        d->print(p2);
    }
    return 0;
}