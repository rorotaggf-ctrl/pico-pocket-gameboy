#ifndef HW_BRIDGE_H
#define HW_BRIDGE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_GRAY    0x7BEF

#define BTN_UP        (1 << 0)
#define BTN_DOWN      (1 << 1)
#define BTN_LEFT      (1 << 2)
#define BTN_RIGHT     (1 << 3)
#define BTN_A         (1 << 4)
#define BTN_B         (1 << 5)

void hw_fill_screen(uint16_t color);
void hw_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void hw_draw_pixel(int16_t x, int16_t y, uint16_t color);
void hw_draw_text(int16_t x, int16_t y, const char* txt, uint16_t color, uint8_t size);
uint8_t hw_read_buttons(void);
void hw_beep(uint16_t freq, uint16_t dur_ms);
uint32_t hw_millis(void);
void hw_delay(uint32_t ms);


void hw_save_score(const char* game_key, uint16_t score);
void hw_get_top3(const char* game_key, uint16_t* scores);

#ifdef __cplusplus
}
#endif

#endif