#include "mainscreen.h"
#include "settings.h"

static const char* games[] = {
    "1. SNAKE", "2. FLAPPY", "3. TETRIS", "4. PONG", "5. WOLF 3D",
    "6. INVADERS", "7. BREAKOUT", "8. LANDER", "9. DINO", "10. SETTINGS"
};

void main_draw(Adafruit_ST7789* tft, uint8_t wahl) {
    uint8_t thm = get_ui_theme();
    uint16_t bg_col  = (thm == 1) ? 0x2000 : ST77XX_BLACK;
    uint16_t tit_col = (thm == 1) ? ST77XX_RED : ((thm == 2) ? 0x7BEF : ST77XX_WHITE);
    uint16_t act_col = (thm == 1) ? ST77XX_RED : ((thm == 2) ? ST77XX_YELLOW : ST77XX_GREEN);

    tft->fillScreen(bg_col);

    // Deko bei Doom Theme
    if (thm == 1) {
        tft->fillRect(0, 0, 240, 4, ST77XX_RED);
        tft->fillRect(0, 236, 240, 4, ST77XX_RED);
        tft->fillRect(10, 42, 220, 2, 0x8000);
    }

    tft->setTextSize(3);
    tft->setCursor(35, 10);
    tft->setTextColor(tit_col);
    tft->print(thm == 1 ? "SLAYER" : "POCKET");

    uint8_t start = (wahl > 4) ? wahl - 4 : 0;
    if (start > 5) start = 5;

    for (uint8_t i = 0; i < 5; i++) {
        uint8_t idx = start + i;
        int16_t y = 55 + (i * 35);
        tft->setTextSize(2);
        tft->setTextColor(idx == wahl ? act_col : ST77XX_WHITE);
        tft->setCursor(20, y);
        tft->print(games[idx]);
    }
}