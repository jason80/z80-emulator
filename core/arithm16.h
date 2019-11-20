#ifndef __ARITHM_16_H
#define __ARITHM_16_H

#include <inttypes.h>

void add16(uint16_t* result, uint16_t* reg16);
void adc16(uint16_t* result, uint16_t* reg16);
void sbc16(uint16_t* result, uint16_t* reg16);

void inc_dec_16(uint16_t* reg16, int p);

#endif
