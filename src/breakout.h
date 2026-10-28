#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void brk_init(void);
uint8_t brk_run(void);

#ifdef __cplusplus
}
#endif

#endif