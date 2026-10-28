#include "lander.h"
#include "hw_bridge.h"

static float sx = 110.0f, sy = 30.0f;
static float vx = 0.0f, vy = 0.0f;
static uint16_t fl = 500;

void lnd_init(void) {
    sx = 110.0f; sy = 30.0f;
    vx = 0.5f; vy = 0.0f;
    fl = 500;
    hw_screen(c_black);
    hw_text(60, 10, "LUNAR LANDER", c_cyan, 2);
    hw_frect(90, 220, 60, 4, c_yellow);
}

uint8_t lnd_run(void) {
    uint8_t b = hw_btns();
    if (b & b_b) return 1;

    hw_frect((int16_t)sx, (int16_t)sy, 8, 8, c_black);

    vy += 0.05f;
    if ((b & b_a) && fl > 0) {
        vy -= 0.12f;
        fl--;
        hw_beep(120, 10);
    }
    if ((b & b_left)  && fl > 0) { vx -= 0.04f; fl--; }
    if ((b & b_right) && fl > 0) { vx += 0.04f; fl--; }

    sx += vx;
    sy += vy;

    if (sy >= 212) {
        if (sx >= 90 && sx <= 142 && vy < 1.0f) {
            hs_save("lnd", fl);
            hw_text(60, 100, "LANDED!", c_green, 2);
        } else {
            hw_text(60, 100, "CRASHED!", c_red, 2);
        }
        hw_wait(1500);
        return 1;
    }

    hw_frect((int16_t)sx, (int16_t)sy, 8, 8, c_white);
    hw_wait(20);
    return 0;
}