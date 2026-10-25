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


<img width="4143" height="5912" alt="gameboy_zeichnung" src="https://github.com/user-attachments/assets/0560cf1a-50d1-4c12-a404-274c0fb4b627" />

<img width="754" height="536" alt="the_gameboy — Schaltplaneditor 25 10 2026 16_54_02" src="https://github.com/user-attachments/assets/0495b00e-4de3-4615-bc45-eeac114f1392" />

<img width="554" height="697" alt="3D-Betrachter 25 10 2026 16_53_29" src="https://github.com/user-attachments/assets/270e60c3-7de3-459a-8c90-27eacc1d9b16" />

<img width="769" height="899" alt="3D-Betrachter 25 10 2026 16_53_06" src="https://github.com/user-attachments/assets/2590f7fe-4fb1-43e5-8c40-c3d473d6f2fc" />
