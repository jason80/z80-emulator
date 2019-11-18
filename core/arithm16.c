#include "arithm16.h"

#include "cpu.h"

void add16(uint16_t* result, uint16_t* reg16) {
	uint32_t res;
	
	res = *result + *reg16;
	
	FLAG_H = (((*result & 0x0FFF) + (*reg16 & 0x0FFF)) & 0x1000) ? 1 : 0;
	FLAG_C = (res > 0xFFFF) ? 1 : 0;
	FLAG_N = 0;
	
	*result = (uint16_t) res;
	
	cpu->ts = 11;
}
