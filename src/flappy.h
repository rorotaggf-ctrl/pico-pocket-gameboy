#ifndef FLAPPY_H
#define FLAPPY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

void flappy_setup(Adafruit_ST7789 *d);
int flappy_loop(Adafruit_ST7789 *d);

#endif