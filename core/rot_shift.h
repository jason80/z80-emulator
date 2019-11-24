#ifndef __ROT_SHIFT_H
#define __ROT_SHIFT_H

#include <inttypes.h>

void rlca(void);
void rrca(void);
void rla(void);
void rra(void);

void rlc(uint8_t* reg8);
void rlc_relative(uint16_t reg16);

#endif
