#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#include "mainscreen.h"
#include "settings.h"
#include "sound.h"
#include "screensaver.h"

#include "snake.h"
#include "flappy.h"
#include "tetris.h"
#include "pong.h"
#include "wolf.h"

#include "invaders.h"
#include "breakout.h"
#include "lander.h"
#include "dino.h"

#define mosi 23
#define sclk 18
#define cs -1
#define dc 2
#define rst 4

Adafruit_ST7789 tft = Adafruit_ST7789(cs, dc, mosi, sclk, rst);

static const uint8_t p_up   = 32;
static const uint8_t p_down = 33;
static const uint8_t p_l    = 25;
static const uint8_t p_r    = 26;
static const uint8_t p_a    = 27;
static const uint8_t p_b    = 14;
static const uint8_t p_spk  = 13;

static uint8_t wahl = 0;
static uint8_t st = 0;
static unsigned long t_idle = 0;
static int8_t last_saver = -1;

static uint8_t get_next_saver() {
    uint8_t cfg = get_saver_mode();
    if (cfg != 0) {
        last_saver = cfg - 1;
        return last_saver;
    }
    uint8_t r;
    do {
        r = random(0, 4);
    } while (r == last_saver);
    last_saver = r;
    return r;
}

// Prozedurale Maske für Back in Black (Gitarren-Silhouette & Blitz)
static void draw_bib_mask() {
    tft.fillScreen(ST77XX_BLACK);
    tft.fillRect(115, 20, 10, 80, 0x7BEF);
    tft.fillCircle(120, 130, 35, 0x39E7);
    tft.fillCircle(120, 175, 45, 0x39E7);
    tft.fillCircle(120, 150, 15, ST77XX_BLACK);

    tft.drawLine(100, 70, 140, 70, ST77XX_WHITE);
    tft.drawLine(100, 190, 140, 190, ST77XX_WHITE);

    tft.setTextSize(2);
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(45, 95);
    tft.print("BACK IN BLACK");
}

// Prozedurale Maske für Doom (Blutiger Schädel & Splatter)
static void draw_doom_mask() {
    tft.fillScreen(0x2000);
    for (int i = 0; i < 40; i++) {
        tft.fillCircle(random(10, 230), random(10, 230), random(2, 6), ST77XX_RED);
    }

    tft.fillRoundRect(85, 70, 70, 65, 12, 0xDEFB);
    tft.fillRect(95, 120, 50, 25, 0xDEFB);
    tft.fillCircle(105, 95, 9, 0x2000);
    tft.fillCircle(135, 95, 9, 0x2000);
    tft.fillTriangle(120, 105, 115, 118, 125, 118, 0x2000);

    for (int t = 0; t < 5; t++) {
        tft.drawLine(99 + t * 9, 132, 99 + t * 9, 145, 0x2000);
    }

    tft.setTextSize(3);
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(55, 160);
    tft.print("DOOM");

    tft.setTextSize(1);
    tft.setTextColor(ST77XX_YELLOW);
    tft.setCursor(20, 200);
    tft.print("THE ONLY THING THEY FEAR IS YOU");
}

void setup() {
    pinMode(p_up, INPUT_PULLUP);
    pinMode(p_down, INPUT_PULLUP);
    pinMode(p_l, INPUT_PULLUP);
    pinMode(p_r, INPUT_PULLUP);
    pinMode(p_a, INPUT_PULLUP);
    pinMode(p_b, INPUT_PULLUP);
    pinMode(p_spk, OUTPUT);

    tft.init(240, 240, SPI_MODE3);
    tft.setRotation(2);

    set_init(&tft);

    // Easter Egg Prüfung bei Boot: Taste A gedrückt = DOOM
    if (digitalRead(p_a) == LOW) {
        draw_doom_mask();
        if (get_sound_enabled()) doom_intro(p_spk);
        delay(600);
    }
    // Taste B gedrückt = Back in Black
    else if (digitalRead(p_b) == LOW) {
        draw_bib_mask();
        if (get_sound_enabled()) bib_intro(p_spk);
        delay(600);
    }

    main_draw(&tft, wahl);
    t_idle = millis();
}

void loop() {
    if (st == 0) {
        uint32_t tout = get_saver_timeout();
        if (tout != 0xFFFFFFFF && millis() - t_idle > tout) {
            st = 99;
            saver_start(&tft, get_next_saver());
            return;
        }

        if (digitalRead(p_up) == LOW) {
            t_idle = millis();
            wahl = (wahl > 0) ? wahl - 1 : 9;
            main_draw(&tft, wahl);
            delay(170);
        }
        if (digitalRead(p_down) == LOW) {
            t_idle = millis();
            wahl = (wahl < 9) ? wahl + 1 : 0;
            main_draw(&tft, wahl);
            delay(170);
        }
        if (digitalRead(p_a) == LOW) {
            delay(180);
            st = wahl + 1;
            if (st == 1)       snake_setup(&tft);
            else if (st == 2)  flappy_setup(&tft);
            else if (st == 3)  tetris_setup(&tft);
            else if (st == 4)  pong_setup(&tft);
            else if (st == 5)  wolf_setup(&tft);
            else if (st == 6)  inv_init();
            else if (st == 7)  brk_init();
            else if (st == 8)  lnd_init();
            else if (st == 9)  din_init();
            else if (st == 10) set_init(&tft);
        }
    }
    else if (st == 1 && snake_loop(&tft) == 1) { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 2 && flappy_loop(&tft) == 1){ st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 3 && tetris_loop(&tft) == 1){ st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 4 && pong_loop(&tft) == 1)  { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 5 && wolf_loop(&tft) == 1)  { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 6 && inv_run() == 1)        { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 7 && brk_run() == 1)        { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 8 && lnd_run() == 1)        { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 9) {
        uint8_t b = 0;
        if (digitalRead(p_up)   == LOW) b |= (1 << 0);
        if (digitalRead(p_down) == LOW) b |= (1 << 1);
        if (digitalRead(p_l)    == LOW) b |= (1 << 2);
        if (digitalRead(p_r)    == LOW) b |= (1 << 3);
        if (digitalRead(p_a)    == LOW) b |= (1 << 4);
        if (digitalRead(p_b)    == LOW) b |= (1 << 5);

        if (din_run(b) == 1) {
            st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200);
        }
        delay(15);
    }
    else if (st == 10 && set_run(&tft) == 1)   { st = 0; t_idle = millis(); main_draw(&tft, wahl); delay(200); }
    else if (st == 99) {
        saver_tick(&tft);
        if (digitalRead(p_up) == LOW || digitalRead(p_down) == LOW || 
            digitalRead(p_l) == LOW  || digitalRead(p_r) == LOW || 
            digitalRead(p_a) == LOW  || digitalRead(p_b) == LOW) {
            st = 0;
            t_idle = millis();
            main_draw(&tft, wahl);
            delay(200);
        }
    }
}