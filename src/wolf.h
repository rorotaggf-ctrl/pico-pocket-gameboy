#ifndef WOLF_H
#define WOLF_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

void wolf_setup(Adafruit_ST7789 *d);
int wolf_loop(Adafruit_ST7789 *d);

#endif