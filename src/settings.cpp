#include "settings.h"
#include "sound.h"
#include <Arduino.h>
#include <Preferences.h>

static const uint8_t p_up   = 32;
static const uint8_t p_down = 33;
static const uint8_t p_l    = 25;
static const uint8_t p_r    = 26;
static const uint8_t p_a    = 27;
static const uint8_t p_b    = 14;
static const uint8_t p_spk  = 13;

static Preferences pref;

static uint8_t sel = 0;
static bool redraw = true;
static uint8_t sub_egg = 0; // 0=Main Settings, 1=Easter Egg Menü
static uint8_t egg_sel = 0;

static uint8_t  cfg_saver_mode = 0;
static uint8_t  cfg_timeout_idx = 1;
static bool     cfg_sound = true;
static uint8_t  cfg_theme = 0;

static const char* saver_names[] = {"RANDOM", "DVD", "RR", "MATRIX", "STARFIELD"};
static const char* timeout_names[] = {"15s", "30s", "60s", "AUS"};
static const uint32_t timeouts_ms[] = {15000, 30000, 60000, 0xFFFFFFFF};

static const char* egg_names[] = {
    "1. RIFF: DOOM",
    "2. RIFF: BIB",
    "3. RIFF: STAR WARS",
    "4. RIFF: MONEY 4 NOTH",
    "5. THEME: STANDARD",
    "6. THEME: DOOM BLOOD",
    "7. THEME: BIB DARK"
};

uint8_t  get_saver_mode(void)    { return cfg_saver_mode; }
uint32_t get_saver_timeout(void) { return timeouts_ms[cfg_timeout_idx]; }
bool     get_sound_enabled(void) { return cfg_sound; }
uint8_t  get_ui_theme(void)      { return cfg_theme; }

void set_init(Adafruit_ST7789* d) {
    pref.begin("sys_cfg", true);
    cfg_saver_mode  = pref.getUChar("sav_m", 0);
    cfg_timeout_idx = pref.getUChar("sav_t", 1);
    cfg_sound       = pref.getBool("snd", true);
    cfg_theme       = pref.getUChar("thm", 0);
    pref.end();

    sel = 0;
    sub_egg = 0;
    redraw = true;
}

uint8_t set_run(Adafruit_ST7789* d) {
    if (digitalRead(p_b) == LOW) {
        if (sub_egg == 1) {
            sub_egg = 0;
            redraw = true;
            delay(180);
            return 0;
        }
        pref.begin("sys_cfg", false);
        pref.putUChar("sav_m", cfg_saver_mode);
        pref.putUChar("sav_t", cfg_timeout_idx);
        pref.putBool("snd", cfg_sound);
        pref.putUChar("thm", cfg_theme);
        pref.end();

        delay(180);
        return 1;
    }

    if (redraw) {
        d->fillScreen(cfg_theme == 1 ? 0x2000 : ST77XX_BLACK);
        d->setTextSize(2);

        if (sub_egg == 0) {
            d->setTextColor(cfg_theme == 1 ? ST77XX_RED : ST77XX_YELLOW);
            d->setCursor(65, 8);
            d->print("SETTINGS");

            d->setTextColor(sel == 0 ? ST77XX_GREEN : ST77XX_WHITE);
            d->setCursor(15, 40);
            d->print("SAVER: "); d->print(saver_names[cfg_saver_mode]);

            d->setTextColor(sel == 1 ? ST77XX_GREEN : ST77XX_WHITE);
            d->setCursor(15, 75);
            d->print("TIME : "); d->print(timeout_names[cfg_timeout_idx]);

            d->setTextColor(sel == 2 ? ST77XX_GREEN : ST77XX_WHITE);
            d->setCursor(15, 110);
            d->print("SOUND: "); d->print(cfg_sound ? "AN" : "AUS");

            d->setTextColor(sel == 3 ? ST77XX_GREEN : ST77XX_WHITE);
            d->setCursor(15, 145);
            d->print("EASTER EGGS ->");

            d->setTextColor(sel == 4 ? ST77XX_GREEN : ST77XX_WHITE);
            d->setCursor(15, 180);
            d->print("CLR ALL SCORES");

            d->setTextSize(1);
            d->setTextColor(ST77XX_WHITE);
            d->setCursor(20, 220);
            d->print("DPAD: WAHL | B: SPEICHERN");
        } else {
            d->setTextColor(ST77XX_RED);
            d->setCursor(45, 8);
            d->print("EASTER EGGS");

            for (uint8_t i = 0; i < 5; i++) {
                uint8_t idx = (egg_sel > 3) ? (egg_sel - 3 + i) : i;
                if (idx > 6) break;
                d->setTextColor(idx == egg_sel ? ST77XX_GREEN : ST77XX_WHITE);
                d->setCursor(15, 40 + i * 35);
                d->print(egg_names[idx]);
            }

            d->setTextSize(1);
            d->setTextColor(ST77XX_WHITE);
            d->setCursor(25, 220);
            d->print("A: SPIELEN/SET | B: ZURUECK");
        }
        redraw = false;
    }

    if (digitalRead(p_up) == LOW) {
        if (sub_egg == 0) sel = (sel > 0) ? sel - 1 : 4;
        else egg_sel = (egg_sel > 0) ? egg_sel - 1 : 6;
        redraw = true;
        delay(160);
    }
    if (digitalRead(p_down) == LOW) {
        if (sub_egg == 0) sel = (sel < 4) ? sel + 1 : 0;
        else egg_sel = (egg_sel < 6) ? egg_sel + 1 : 0;
        redraw = true;
        delay(160);
    }

    if (digitalRead(p_r) == LOW || digitalRead(p_a) == LOW) {
        if (sub_egg == 0) {
            if (sel == 0) { cfg_saver_mode = (cfg_saver_mode + 1) % 5; redraw = true; delay(170); }
            else if (sel == 1) { cfg_timeout_idx = (cfg_timeout_idx + 1) % 4; redraw = true; delay(170); }
            else if (sel == 2) { cfg_sound = !cfg_sound; if (cfg_sound) tone(p_spk, 880, 50); redraw = true; delay(170); }
            else if (sel == 3 && digitalRead(p_a) == LOW) { sub_egg = 1; egg_sel = 0; redraw = true; delay(180); }
            else if (sel == 4 && digitalRead(p_a) == LOW) {
                Preferences p;
                p.begin("game", false);  p.clear(); p.end();
                p.begin("h_inv", false); p.clear(); p.end();
                p.begin("h_brk", false); p.clear(); p.end();
                p.begin("h_lnd", false); p.clear(); p.end();
                p.begin("h_din", false); p.clear(); p.end();
                d->setCursor(15, 200);
                d->setTextSize(2);
                d->setTextColor(ST77XX_RED);
                d->print("GELOESCHT!");
                if (cfg_sound) tone(p_spk, 440, 100);
                delay(500);
                redraw = true;
            }
        } else if (digitalRead(p_a) == LOW) {
            if (egg_sel == 0)      doom_intro(p_spk);
            else if (egg_sel == 1) bib_intro(p_spk);
            else if (egg_sel == 2) starwars_intro(p_spk);
            else if (egg_sel == 3) money_intro(p_spk);
            else if (egg_sel == 4) { cfg_theme = 0; redraw = true; }
            else if (egg_sel == 5) { cfg_theme = 1; redraw = true; }
            else if (egg_sel == 6) { cfg_theme = 2; redraw = true; }
            delay(180);
        }
    }

    if (sub_egg == 0 && digitalRead(p_l) == LOW) {
        if (sel == 0)      { cfg_saver_mode = (cfg_saver_mode > 0) ? cfg_saver_mode - 1 : 4; redraw = true; delay(170); }
        else if (sel == 1) { cfg_timeout_idx = (cfg_timeout_idx > 0) ? cfg_timeout_idx - 1 : 3; redraw = true; delay(170); }
        else if (sel == 2) { cfg_sound = !cfg_sound; if (cfg_sound) tone(p_spk, 880, 50); redraw = true; delay(170); }
    }

    return 0;
}