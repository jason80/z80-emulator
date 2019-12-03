#include "bit.h"

#include "cpu.h"

void bit_test(uint8_t* reg8, uint8_t bit) {
	FLAG_Z = (*reg8 & (1 << bit)) ? 0 : 1;
	FLAG_H = 1; FLAG_N = 0;
	cpu->ts = 8;
}

void bit_set(uint8_t* reg8, uint8_t bit) {
	*reg8 |= (1 << bit);
	cpu->ts = 8;
}

void bit_reset(uint8_t* reg8, uint8_t bit) {
	uint8_t mask = (1 << bit);
	mask = ~mask;
	*reg8 &= mask;
	cpu->ts = 8;
}

void bit_test_relative(uint16_t reg16, uint8_t bit) {
	bit_test(&cpu->mem[reg16 + BRL], bit);
	cpu->ts = 20;
}

void bit_set_relative(uint16_t reg16, uint8_t bit) {
	bit_set(&cpu->mem[reg16 + BRL], bit);
	cpu->ts = 23;
}

void bit_reset_relative(uint16_t reg16, uint8_t bit) {
	bit_reset(&cpu->mem[reg16 + BRL], bit);
	cpu->ts = 23;
}
