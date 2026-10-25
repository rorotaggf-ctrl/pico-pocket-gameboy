# Pico Pocket Gameboy

A small retro handheld console built with an ESP32 for **Hack Club Half-Life (Week 1)**[cite: 4, 5].

I designed a custom PCB in KiCad and everything uses through-hole parts so it's super easy to solder by hand[cite: 5].

## Features

- **CPU:** ESP32 NodeMCU (USB-C, dual-core, plenty of speed)[cite: 4, 5]
- **Display:** 1.3" IPS color display (240 x 240, ST7789)[cite: 4, 5]
- **Buttons:** 8 clicky buttons (D-Pad, A/B, Start/Select)[cite: 4, 5]
- **Sound:** Piezo buzzer for 8-bit beeps and game sounds[cite: 4, 5]
- **Power:** Slide switch on the right side to turn it on/off[cite: 5]
- **PCB:** 70 x 120 mm custom PCB[cite: 5]

## Pinout

Everything is plugged into female pin headers so I can swap out the ESP32 or screen if something breaks[cite: 5].

| Part | Pin | ESP32 GPIO | Notes |
| :--- | :--- | :--- | :--- |
| **Screen** | SCL / SDA | GPIO 18 / GPIO 23 | Hardware SPI[cite: 4, 5] |
| | RES / DC | GPIO 4 / GPIO 2 | Reset & Command pins[cite: 4, 5] |
| **D-Pad** | Up / Down | GPIO 32 / GPIO 33 | Active LOW[cite: 4] |
| | Left / Right | GPIO 25 / GPIO 26 | Active LOW[cite: 4] |
| **Action** | A / B | GPIO 27 / GPIO 14 | Active LOW (B = Menu Return)[cite: 4] |
| **Buzzer** | Plus (+) | GPIO 13 | PWM audio[cite: 4] |
| **Switch** | Center pin | VIN | Power on/off[cite: 5] |

## Bill of Materials

> [!NOTE]
> This parts list is mirrored from [Half Life](https://halflife.hackclub.com).

| Week | Tier | Parts funding |
| :--- | :--- | :--- |
| Week 1 | Tier 1 | $30.00 |

| Part | What it's for | Qty | Unit | Total | Vendor |
| :--- | :--- | :--- | :--- | :--- | :--- |
| [1.3" SPI TFT LCD (ST7789)](https://www.amazon.de/dp/B09Z299F3Q/?smid=A3LA1TDA4Q3SUA&tag=preisvergleich-idealode-21&linkCode=asn&creative=6742&camp=1638&creativeASIN=B09Z299F3Q&ascsubtag=2026-10-06_9bd703fbc3abd0e9a70a7dc74d566bbac1b916e57de4f8494cb3f283914ffeb3&th=1&psc=1) | that we can see the game | 1 | $7.87 | $7.87 | [Amazon](https://www.amazon.de/dp/B09Z299F3Q/?smid=A3LA1TDA4Q3SUA&tag=preisvergleich-idealode-21&linkCode=asn&creative=6742&camp=1638&creativeASIN=B09Z299F3Q&ascsubtag=2026-10-06_9bd703fbc3abd0e9a70a7dc74d566bbac1b916e57de4f8494cb3f283914ffeb3&th=1&psc=1) |
| [Custom 2-Layer PCB (5 copies)](https://jlcpcb.com/quote) | Main gameboy PCB board manufacturing | 1 | $8.10 | $8.10 | [JLCPCB](https://jlcpcb.com/quote) |
| [ESP32 USB C mit CP2102 Chip NodeMCU](https://www.ebay.de/itm/377544239165) | The CPU | 1 | $12.25 | $12.25 | [ebay](https://www.ebay.de/itm/377544239165) |
| **Parts subtotal** | — | — | — | **$28.22** | — |
| **Tax & shipping** | — | — | — | **$0.00** | — |
| **Total** | — | — | — | **$28.22** | — |

*$1.78 left of the tier's funding.*

## Software & Games

Coding this in **VS Code** with PlatformIO and the Arduino framework[cite: 4, 5].

- [x] Hardware test (check all buttons, screen and buzzer)[cite: 5]
- [x] **Snake:** Classic arcade snake with dynamic speed progression and persistent flash highscore saving (`Preferences.h`)[cite: 4].
- [x] **Flappy Bird:** Physics-based flapping mechanics with shrinking tube gaps and highscore tracking[cite: 4].
- [x] **Tetris:** 4-block piece rotation, line clears, game over detection and scaling fall-speed[cite: 4].
- [x] **Pong:** 1-Player retro pong against an automated bot with 3 selectable difficulty levels (Leicht, Mittel, Schwer)[cite: 4].
- [x] **Wolfenstein 3D:** Lightweight pseudo-3D DDA raycasting engine with shooting mechanics and destroyable wall blocks.
- [x] **Screensavers:** 4 idle modes kicking in after 30s (Starfield warp, Matrix code rain, bouncing DVD logo, bouncing RR logo)[cite: 4].
- [x] **Sound & Easter Egg:** Chiptune audio tone effects and secret boot intro (AC/DC - Back in Black) triggered on hold.

---

### Hardware & PCB Previews

<img width="4143" height="5912" alt="gameboy_zeichnung" src="https://github.com/user-attachments/assets/0560cf1a-50d1-4c12-a404-274c0fb4b627" />

<img width="754" height="536" alt="the_gameboy — Schaltplaneditor 25 10 2026 16_54_02" src="https://github.com/user-attachments/assets/0495b00e-4de3-4615-bc45-eeac114f1392" />

<img width="554" height="697" alt="3D-Betrachter 25 10 2026 16_53_29" src="https://github.com/user-attachments/assets/270e60c3-7de3-459a-8c90-27eacc1d9b16" />

<img width="769" height="899" alt="3D-Betrachter 25 10 2026 16_53_06" src="https://github.com/user-attachments/assets/2590f7fe-4fb1-43e5-8c40-c3d473d6f2fc" />
