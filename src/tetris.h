#ifndef TETRIS_H
#define TETRIS_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

void tetris_setup(Adafruit_ST7789 *d);
int tetris_loop(Adafruit_ST7789 *d);

#endif