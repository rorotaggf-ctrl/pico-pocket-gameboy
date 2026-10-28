#ifndef HW_BRIDGE_H
#define HW_BRIDGE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Farben klein
#define c_black   0x0000
#define c_white   0xFFFF
#define c_red     0xF800
#define c_green   0x07E0
#define c_blue    0x001F
#define c_yellow  0xFFE0
#define c_cyan    0x07FF
#define c_magenta 0xF81F
#define c_gray    0x7BEF

// Tastenmasken klein
#define b_up    (1 << 0)
#define b_down  (1 << 1)
#define b_left  (1 << 2)
#define b_right (1 << 3)
#define b_a     (1 << 4)
#define b_b     (1 << 5)

// Kurze HW-Funktionen
void     hw_screen(uint16_t c);
void     hw_frect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
void     hw_pixel(int16_t x, int16_t y, uint16_t c);
void     hw_text(int16_t x, int16_t y, const char* s, uint16_t c, uint8_t sz);
uint8_t  hw_btns(void);
void     hw_beep(uint16_t f, uint16_t d);
uint32_t hw_time(void);
void     hw_wait(uint32_t ms);

// Highscore Top 3
void hs_save(const char* k, uint16_t val);
void hs_get(const char* k, uint16_t* out);

#ifdef __cplusplus
}
#endif

#endif