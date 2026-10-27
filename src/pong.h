#ifndef PONG_H
#define PONG_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

void pong_setup(Adafruit_ST7789 *d);
int pong_loop(Adafruit_ST7789 *d);

#endif