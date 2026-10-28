#include "breakout.h"
#include "hw_bridge.h"

static int16_t pdx = 100;
static int16_t bx = 120, by = 150;
static int8_t  bvx = 2, bvy = -3;
static uint8_t bks[24];
static uint16_t sc = 0;

void brk_init(void) {
    pdx = 100;
    bx = 120; by = 150;
    bvx = 2; bvy = -3;
    sc = 0;
    for (int i = 0; i < 24; i++) bks[i] = 1;
    hw_screen(c_black);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 6; c++) {
            hw_frect(10 + c * 37, 30 + r * 15, 32, 10, c_magenta);
        }
    }
}

uint8_t brk_run(void) {
    uint8_t b = hw_btns();
    if (b & b_b) {
        hs_save("brk", sc);
        return 1;
    }

    hw_frect(pdx, 220, 36, 6, c_black);
    if ((b & b_left)  && pdx > 5)   pdx -= 4;
    if ((b & b_right) && pdx < 195) pdx += 4;
    hw_frect(pdx, 220, 36, 6, c_green);

    hw_frect(bx, by, 4, 4, c_black);
    bx += bvx;
    by += bvy;

    if (bx <= 0 || bx >= 236) { bvx = -bvx; hw_beep(400, 10); }
    if (by <= 20)             { bvy = -bvy; hw_beep(400, 10); }

    if (by >= 216 && by <= 222 && bx >= pdx && bx <= pdx + 36) {
        bvy = -bvy;
        hw_beep(600, 15);
    }

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 6; c++) {
            int idx = r * 6 + c;
            if (bks[idx]) {
                int16_t rx = 10 + c * 37;
                int16_t ry = 30 + r * 15;
                if (bx >= rx && bx <= rx + 32 && by >= ry && by <= ry + 10) {
                    bks[idx] = 0;
                    hw_frect(rx, ry, 32, 10, c_black);
                    bvy = -bvy;
                    sc += 10;
                    hw_beep(800, 15);
                }
            }
        }
    }

    if (by > 235) {
        hs_save("brk", sc);
        return 1;
    }

    hw_frect(bx, by, 4, 4, c_white);
    hw_wait(16);
    return 0;
}