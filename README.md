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

| Part | What it's for | Qty | Price | Where | 
| ----- | ----- | ----- | ----- | ----- | 
| 1.3" SPI TFT LCD (ST7789) | The screen | 1 | \$2.23 | AliExpress | 
| Mini Slide Switch (SPDT) | Power switch (angled) | 1 | \$1.85 | AliExpress | 
| Passive Piezo Buzzer | Retro sounds | 1 | \$2.01 | AliExpress | 
| 100nF Ceramic Capacitors | Smooth power supply | 1 | \$2.45 | AliExpress | 
| 2.54mm Pin Header Kit | Sockets for ESP & screen | 1 | \$7.27 | Amazon | 
| Custom 2-Layer PCB | Main board | 5 | \$2.00 | JLCPCB | 
| ESP32 NodeMCU (USB-C) | The CPU | 1 | \$8.51 | Amazon | 
| Shipping & Tax | Shipping costs | — | \$3.39 | Various | 
| **Total** |  |  | **\$29.71** | (\$0.29 left) | 

## Software & Games

Coding this in **VS Code** with the Arduino extension.

* \[ \] Hardware test (check all 8 buttons, screen and buzzer)

* \[ \] Snake

* \[ \] Flappy Bird
