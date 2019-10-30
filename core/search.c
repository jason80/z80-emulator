#include "search.h"

#include "../core/cpu.h"

void cpi(void) {
	int16_t result;
	result = A - cpu->mem[HL];
	
	HL ++; BC --;
	
	FLAG_S = (result < 0) ? 1 : 0;
	FLAG_Z = (result == 0) ? 1 : 0;
	FLAG_H = ((A & 0x0F) - (cpu->mem[HL] & 0x0F)) & 0x10;
	FLAG_PV = (BC != 0) ? 1 : 0;
	FLAG_N = 1;
	
	cpu->ts = 16;
}
