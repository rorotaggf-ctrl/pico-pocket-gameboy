#ifndef SNAKE_H
#define SNAKE_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

void snake_setup(Adafruit_ST7789 *d);
int snake_loop(Adafruit_ST7789 *d);

#endif