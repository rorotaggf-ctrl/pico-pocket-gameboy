#ifndef DINO_H
#define DINO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void din_init(void);
uint32_t din_run(uint32_t b);

#ifdef __cplusplus
}
#endif

#endif