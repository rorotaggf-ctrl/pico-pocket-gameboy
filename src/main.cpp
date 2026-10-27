#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "snake.h"
#include "flappy.h"
#include "tetris.h"
#include "pong.h"
#include "wolf.h"
#include "screensaver.h"
#include "sound.h"

#define mosi 23
#define sclk 18
#define cs -1
#define dc 2
#define rst 4

Adafruit_ST7789 tft = Adafruit_ST7789(cs, dc, mosi, sclk, rst);

static const uint8_t m_oben = 32;
static const uint8_t m_unten = 33;
static const uint8_t m_a = 27;
static const uint8_t m_b = 14;
static const uint8_t m_pieps = 13;

static uint8_t wahl = 0;
static uint8_t zustand = 0;
static unsigned long inaktiv_t = 0;

void mal_menu()
{
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(3);
    tft.setCursor(35, 12);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("POCKET");

    tft.setTextSize(2);
    tft.setTextColor(wahl == 0 ? ST77XX_GREEN : ST77XX_WHITE);
    tft.setCursor(45, 58);
    tft.print("1. SNAKE");

    tft.setTextColor(wahl == 1 ? ST77XX_GREEN : ST77XX_WHITE);
    tft.setCursor(45, 93);
    tft.print("2. FLAPPY");

    tft.setTextColor(wahl == 2 ? ST77XX_GREEN : ST77XX_WHITE);
    tft.setCursor(45, 128);
    tft.print("3. TETRIS");

    tft.setTextColor(wahl == 3 ? ST77XX_GREEN : ST77XX_WHITE);
    tft.setCursor(45, 163);
    tft.print("4. PONG");

    tft.setTextColor(wahl == 4 ? ST77XX_GREEN : ST77XX_WHITE);
    tft.setCursor(45, 198);
    tft.print("5. WOLF 3D");
}

void setup()
{
    pinMode(m_oben, INPUT_PULLUP);
    pinMode(m_unten, INPUT_PULLUP);
    pinMode(m_a, INPUT_PULLUP);
    pinMode(m_b, INPUT_PULLUP);
    pinMode(m_pieps, OUTPUT);

    tft.init(240, 240, SPI_MODE3);
    tft.setRotation(2);

    if (digitalRead(m_b) == LOW)
    {
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(20, 110);
        tft.setTextSize(2);
        tft.setTextColor(ST77XX_RED);
        tft.print("BACK IN BLACK");
        bib_intro(m_pieps);
    }

    mal_menu();
    inaktiv_t = millis();
}

void loop()
{
    if (zustand == 0)
    {
        if (millis() - inaktiv_t > 30000)
        {
            zustand = 99;
            saver_start(&tft, random(0, 4));
            return;
        }

        if (digitalRead(m_oben) == LOW)
        {
            inaktiv_t = millis();
            wahl = (wahl > 0) ? wahl - 1 : 4;
            mal_menu();
            delay(170);
        }
        if (digitalRead(m_unten) == LOW)
        {
            inaktiv_t = millis();
            wahl = (wahl < 4) ? wahl + 1 : 0;
            mal_menu();
            delay(170);
        }
        if (digitalRead(m_a) == LOW)
        {
            delay(180);
            zustand = wahl + 1;
            if (zustand == 1)
                snake_setup(&tft);
            else if (zustand == 2)
                flappy_setup(&tft);
            else if (zustand == 3)
                tetris_setup(&tft);
            else if (zustand == 4)
                pong_setup(&tft);
            else if (zustand == 5)
                wolf_setup(&tft);
        }
    }
    else if (zustand == 1)
    {
        if (snake_loop(&tft) == 1)
        {
            zustand = 0;
            inaktiv_t = millis();
            mal_menu();
            delay(200);
        }
    }
    else if (zustand == 2)
    {
        if (flappy_loop(&tft) == 1)
        {
            zustand = 0;
            inaktiv_t = millis();
            mal_menu();
            delay(200);
        }
    }
    else if (zustand == 3)
    {
        if (tetris_loop(&tft) == 1)
        {
            zustand = 0;
            inaktiv_t = millis();
            mal_menu();
            delay(200);
        }
    }
    else if (zustand == 4)
    {
        if (pong_loop(&tft) == 1)
        {
            zustand = 0;
            inaktiv_t = millis();
            mal_menu();
            delay(200);
        }
    }
    else if (zustand == 5)
    {
        if (wolf_loop(&tft) == 1)
        {
            zustand = 0;
            inaktiv_t = millis();
            mal_menu();
            delay(200);
        }
    }
    else if (zustand == 99)
    {
        saver_tick(&tft);
        if (digitalRead(m_oben) == LOW || digitalRead(m_unten) == LOW || digitalRead(m_a) == LOW || digitalRead(m_b) == LOW)
        {
            zustand = 0;
            inaktiv_t = millis();
            mal_menu();
            delay(200);
        }
    }
}