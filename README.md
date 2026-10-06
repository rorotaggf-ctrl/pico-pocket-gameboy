# Pico Pocket Gameboy

A small retro handheld console built with an ESP32 for **Hack Club Half-Life (Week 1)**.

I designed a custom PCB in KiCad and everything uses through-hole parts so it's super easy to solder by hand.

## Features

* **CPU:** ESP32 NodeMCU (USB-C, dual-core, plenty of speed)

* **Display:** 1.3" IPS color display ($240 \times 240$, ST7789)

* **Buttons:** 8 clicky buttons (D-Pad, A/B, Start/Select)

* **Sound:** Piezo buzzer for 8-bit beeps and game sounds

* **Power:** Slide switch on the right side to turn it on/off

* **PCB:** $70 \times 120\,\text{mm}$ custom PCB

## Pinout

Everything is plugged into female pin headers so I can swap out the ESP32 or screen if something breaks.

| Part | Pin | ESP32 GPIO | Notes | 
| ----- | ----- | ----- | ----- | 
| **Screen** | SCL / SDA | GPIO 18 / GPIO 23 | Hardware SPI | 
|  | RES / DC | GPIO 4 / GPIO 2 | Reset & Command pins | 
| **D-Pad** | Up / Down | GPIO 13 / GPIO 12 | Active LOW | 
|  | Left / Right | GPIO 14 / GPIO 27 | Active LOW | 
| **Action** | A / B | GPIO 26 / GPIO 25 | Active LOW | 
| **Menu** | Start / Select | GPIO 33 / GPIO 32 | Active LOW | 
| **Buzzer** | Plus (+) | GPIO 15 | PWM audio | 
| **Switch** | Center pin | VIN | Power on/off | 

## Bill of Materials 

For BoM see BOM.md

## Software & Games

Coding this in **VS Code** with the Arduino extension.

My next steps:

* \[ \] Hardware test (check all 8 buttons, screen and buzzer)

* \[ \] Snake

* \[ \] Flappy Bird


