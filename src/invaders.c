#include "invaders.h"
#include "hw_bridge.h"
#include <stdio.h>

static int16_t px = 110;
static int16_t lx = -1, ly = -1;
static uint8_t ali[12];
static int16_t ax = 20, ay = 40;
static int8_t  adir = 2;
static uint16_t sc = 0;
static uint32_t t_step = 0;

void inv_init(void) {
    px = 110;
    lx = -1; ly = -1;
    ax = 20; ay = 40;
    adir = 2;
    sc = 0;
    for (int i = 0; i < 12; i++) ali[i] = 1;
    hw_screen(c_black);
    hw_text(60, 10, "INVADERS", c_green, 2);
    t_step = hw_time();
}

uint8_t inv_run(void) {
    uint8_t b = hw_btns();
    if (b & b_b) {
        hs_save("inv", sc);
        return 1;
    }

    hw_frect(px, 215, 20, 8, c_black);
    if ((b & b_left)  && px > 5)   px -= 3;
    if ((b & b_right) && px < 215) px += 3;
    hw_frect(px, 215, 20, 8, c_blue);

    if ((b & b_a) && ly < 0) {
        lx = px + 9;
        ly = 210;
        hw_beep(800, 20);
    }
    if (ly >= 0) {
        hw_frect(lx, ly, 2, 6, c_black);
        ly -= 6;
        if (ly < 25) {
            ly = -1;
        } else {
            hw_frect(lx, ly, 2, 6, c_yellow);
        }
    }

    if (hw_time() - t_step > 150) {
        t_step = hw_time();
        ax += adir;
        if (ax > 80 || ax < 10) {
            adir = -adir;
            ay += 5;
        }

        uint8_t alive = 0;
        for (int r = 0; r < 2; r++) {
            for (int c = 0; c < 6; c++) {
                int idx = r * 6 + c;
                int16_t ex = ax + c * 22;
                int16_t ey = ay + r * 18;

                if (ali[idx]) {
                    alive++;
                    hw_frect(ex, ey, 14, 10, c_red);
                    if (ly >= 0 && lx >= ex && lx <= ex + 14 && ly >= ey && ly <= ey + 10) {
                        ali[idx] = 0;
                        hw_frect(ex, ey, 14, 10, c_black);
                        hw_frect(lx, ly, 2, 6, c_black);
                        ly = -1;
                        sc += 20;
                        hw_beep(300, 30);
                    }
                } else {
                    hw_frect(ex - 2, ey, 18, 10, c_black);
                }
            }
        }
        if (alive == 0 || ay > 195) {
            hs_save("inv", sc);
            hw_screen(c_black);
            hw_text(60, 110, "GAME OVER", c_red, 2);
            hw_wait(1500);
            return 1;
        }
    }

    char buf[12];
    snprintf(buf, sizeof(buf), "SC:%u", sc);
    hw_text(5, 5, buf, c_white, 1);
    hw_wait(15);
    return 0;
}