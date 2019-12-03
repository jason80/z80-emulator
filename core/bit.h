#ifndef __BIT_H
#define __BIT_H

#include <inttypes.h>

void bit_test(uint8_t* reg8, uint8_t bit);
void bit_set(uint8_t* reg8, uint8_t bit);
void bit_reset(uint8_t* reg8, uint8_t bit);

void bit_test_relative(uint16_t reg16, uint8_t bit);
void bit_set_relative(uint16_t reg16, uint8_t bit);
void bit_reset_relative(uint16_t reg16, uint8_t bit);

#endif
