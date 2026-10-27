#include "tetris.h"
#include <Preferences.h>

static const uint8_t t_oben = 32;
static const uint8_t t_unten = 33;
static const uint8_t t_links = 25;
static const uint8_t t_rechts = 26;
static const uint8_t t_a = 27;
static const uint8_t t_b = 14;
static const uint8_t t_pieps = 13;

static uint8_t grid[10][20];
static uint8_t stein[4][4];
static uint8_t temp[4][4];
static int8_t tx = 3;
static int8_t ty = 0;
static unsigned long tt = 0;
static bool ttot = false;
static uint16_t reihen = 0;
static uint16_t t_hs = 0;
static Preferences p_tet;

static const uint8_t teile[4][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

static void neu_stein()
{
    tx = 3;
    ty = 0;
    uint8_t art = random(0, 4);
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            stein[i][j] = teile[art][i][j];
        }
    }
}

static bool check(int8_t px, int8_t py, uint8_t st[4][4])
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            if (st[i][j])
            {
                int8_t gx = px + j;
                int8_t gy = py + i;
                if (gx < 0 || gx >= 10 || gy >= 20)
                    return false;
                if (gy >= 0 && grid[gx][gy])
                    return false;
            }
        }
    }
    return true;
}

static void zeichne_feld(Adafruit_ST7789 *d)
{
    for (uint8_t x = 0; x < 10; x++)
    {
        for (uint8_t y = 0; y < 20; y++)
        {
            d->fillRect(20 + x * 10, 20 + y * 10, 9, 9, grid[x][y] ? ST77XX_BLUE : ST77XX_BLACK);
        }
    }
}

static void zeichne_stein(Adafruit_ST7789 *d, uint16_t c)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            if (stein[i][j] && (ty + i) >= 0)
            {
                d->fillRect(20 + (tx + j) * 10, 20 + (ty + i) * 10, 9, 9, c);
            }
        }
    }
}

void tetris_setup(Adafruit_ST7789 *d)
{
    pinMode(t_oben, INPUT_PULLUP);
    pinMode(t_unten, INPUT_PULLUP);
    pinMode(t_links, INPUT_PULLUP);
    pinMode(t_rechts, INPUT_PULLUP);
    pinMode(t_a, INPUT_PULLUP);
    pinMode(t_b, INPUT_PULLUP);
    pinMode(t_pieps, OUTPUT);

    p_tet.begin("game", false);
    t_hs = p_tet.getUShort("tet_hs", 0);

    d->fillScreen(ST77XX_BLACK);
    d->drawRect(18, 18, 104, 204, ST77XX_WHITE);
    for (uint8_t x = 0; x < 10; x++)
    {
        for (uint8_t y = 0; y < 20; y++)
        {
            grid[x][y] = 0;
        }
    }
    reihen = 0;
    ttot = false;
    neu_stein();
}

int tetris_loop(Adafruit_ST7789 *d)
{
    if (digitalRead(t_b) == LOW)
        return 1;

    if (ttot)
    {
        if (digitalRead(t_a) == LOW)
            tetris_setup(d);
        return 0;
    }

    if (digitalRead(t_links) == LOW)
    {
        zeichne_stein(d, ST77XX_BLACK);
        if (check(tx - 1, ty, stein))
            tx--;
        zeichne_stein(d, ST77XX_RED);
        delay(90);
    }
    if (digitalRead(t_rechts) == LOW)
    {
        zeichne_stein(d, ST77XX_BLACK);
        if (check(tx + 1, ty, stein))
            tx++;
        zeichne_stein(d, ST77XX_RED);
        delay(90);
    }
    if (digitalRead(t_a) == LOW)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                temp[j][3 - i] = stein[i][j];
            }
        }
        zeichne_stein(d, ST77XX_BLACK);
        if (check(tx, ty, temp))
        {
            for (uint8_t i = 0; i < 4; i++)
            {
                for (uint8_t j = 0; j < 4; j++)
                {
                    stein[i][j] = temp[i][j];
                }
            }
        }
        zeichne_stein(d, ST77XX_RED);
        delay(110);
    }

    uint16_t basis = (reihen < 35) ? (400 - (reihen * 8)) : 90;
    uint16_t fall = (digitalRead(t_unten) == LOW) ? 45 : basis;

    if (millis() - tt > (unsigned long)fall)
    {
        tt = millis();
        zeichne_stein(d, ST77XX_BLACK);
        if (check(tx, ty + 1, stein))
        {
            ty++;
            zeichne_stein(d, ST77XX_RED);
        }
        else
        {
            zeichne_stein(d, ST77XX_BLUE);
            for (uint8_t i = 0; i < 4; i++)
            {
                for (uint8_t j = 0; j < 4; j++)
                {
                    if (stein[i][j] && (ty + i) >= 0)
                    {
                        grid[tx + j][ty + i] = 1;
                    }
                }
            }

            for (int8_t y = 19; y >= 0; y--)
            {
                bool voll = true;
                for (uint8_t x = 0; x < 10; x++)
                {
                    if (!grid[x][y])
                        voll = false;
                }
                if (voll)
                {
                    for (int8_t vy = y; vy > 0; vy--)
                    {
                        for (uint8_t vx = 0; vx < 10; vx++)
                        {
                            grid[vx][vy] = grid[vx][vy - 1];
                        }
                    }
                    for (uint8_t vx = 0; vx < 10; vx++)
                        grid[vx][0] = 0;

                    reihen++;
                    tone(t_pieps, 1000, 50);
                    y++;
                }
            }

            zeichne_feld(d);
            neu_stein();

            if (!check(tx, ty, stein))
            {
                ttot = true;
                tone(t_pieps, 150, 400);

                if (reihen > t_hs)
                {
                    t_hs = reihen;
                    p_tet.putUShort("tet_hs", t_hs);
                }

                d->setCursor(30, 95);
                d->setTextColor(ST77XX_RED);
                d->setTextSize(2);
                d->print("OVER");

                d->setCursor(130, 70);
                d->setTextColor(ST77XX_WHITE);
                d->setTextSize(1);
                d->print("REIHEN:");
                d->setCursor(130, 85);
                d->print(reihen);

                d->setCursor(130, 115);
                d->setTextColor(ST77XX_YELLOW);
                d->print("BEST:");
                d->setCursor(130, 130);
                d->print(t_hs);

                return 0;
            }
            zeichne_stein(d, ST77XX_RED);
        }
    }
    return 0;
}