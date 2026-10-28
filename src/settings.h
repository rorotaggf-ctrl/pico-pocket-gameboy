#ifndef SETTINGS_H
#define SETTINGS_H

#include <Adafruit_ST7789.h>

void set_init(Adafruit_ST7789* d);
uint8_t set_run(Adafruit_ST7789* d);

uint8_t  get_saver_mode(void);
uint32_t get_saver_timeout(void);
bool     get_sound_enabled(void);
uint8_t  get_ui_theme(void);

#endif