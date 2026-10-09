#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

void saver_start(Adafruit_ST7789 *d, uint8_t nr);
void saver_tick(Adafruit_ST7789 *d);

#endif