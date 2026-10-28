#include "hw_bridge.h"
#include <Arduino.h>
#include <Adafruit_ST7789.h>
#include <Preferences.h>

extern Adafruit_ST7789 tft;

static const uint8_t p_up   = 32;
static const uint8_t p_down = 33;
static const uint8_t p_l    = 25;
static const uint8_t p_r    = 26;
static const uint8_t p_a    = 27;
static const uint8_t p_b    = 14;
static const uint8_t p_spk  = 13;

extern "C" {

void hw_screen(uint16_t c) {
    tft.fillScreen(c);
}

void hw_frect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c) {
    tft.fillRect(x, y, w, h, c);
}

void hw_pixel(int16_t x, int16_t y, uint16_t c) {
    tft.drawPixel(x, y, c);
}

void hw_text(int16_t x, int16_t y, const char* s, uint16_t c, uint8_t sz) {
    tft.setCursor(x, y);
    tft.setTextColor(c);
    tft.setTextSize(sz);
    tft.print(s);
}

uint8_t hw_btns(void) {
    uint8_t b = 0;
    if (digitalRead(p_up)   == LOW) b |= b_up;
    if (digitalRead(p_down) == LOW) b |= b_down;
    if (digitalRead(p_l)    == LOW) b |= b_left;
    if (digitalRead(p_r)    == LOW) b |= b_right;
    if (digitalRead(p_a)    == LOW) b |= b_a;
    if (digitalRead(p_b)    == LOW) b |= b_b;
    return b;
}

void hw_beep(uint16_t f, uint16_t d) {
    tone(p_spk, f, d);
}

uint32_t hw_time(void) {
    return millis();
}

void hw_wait(uint32_t ms) {
    delay(ms);
}

void hs_get(const char* k, uint16_t* out) {
    Preferences p;
    char tag[16];
    snprintf(tag, sizeof(tag), "h_%.12s", k);
    p.begin(tag, true);
    out[0] = p.getUShort("s1", 0);
    out[1] = p.getUShort("s2", 0);
    out[2] = p.getUShort("s3", 0);
    p.end();
}

void hs_save(const char* k, uint16_t val) {
    if (val == 0) return;
    uint16_t s[4] = {0, 0, 0, val};
    hs_get(k, s);

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (s[j] > s[i]) {
                uint16_t t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
        }
    }

    Preferences p;
    char tag[16];
    snprintf(tag, sizeof(tag), "h_%.12s", k);
    p.begin(tag, false);
    p.putUShort("s1", s[0]);
    p.putUShort("s2", s[1]);
    p.putUShort("s3", s[2]);
    p.end();
}

}