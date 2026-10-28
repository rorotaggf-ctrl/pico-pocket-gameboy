#ifndef LANDER_H
#define LANDER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void lnd_init(void);
uint8_t lnd_run(void);

#ifdef __cplusplus
}
#endif

#endif