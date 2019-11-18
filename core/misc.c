#include "misc.h"

#include "cpu.h"

void daa(void) {
	
	uint8_t low = A & 0x0F;
	uint8_t hi = (A & 0xF0) >> 4;
	
	if (FLAG_H || low > 9) {
		if (FLAG_N) A -= 0x06;
		else A += 0x06;
	}
	
	if (FLAG_C || hi > 9) {
		if (FLAG_N) A -= 0x60;
		else A += 0x60;
	}
	
	FLAG_C = (A > 0x99) ? 1 : 0;
	FLAG_Z = (A == 0) ? 1 : 0;
	
	cpu->ts = 4;
}

void cpl(void) {
	A = ~A;
	FLAG_H = 1;
	FLAG_N = 1;
	cpu->ts = 4;
}

void neg(void) {
	uint16_t result = 0 - A;
	
	FLAG_S = result < 0 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	FLAG_N = 1;
	
	FLAG_H = ((0 - (A & 0x0F)) & 0x10) > 0 ? 1 : 0;
	
	// Overflow pv
	/*FLAG_PV = 0;
	if ((A & 0x80) != (*reg8 & 0x80))
		if ((A & 0x80) != (result & 0x80))
			FLAG_PV = 1;*/
	FLAG_PV = (A == 0x80) ? 1 : 0;
	
	//FLAG_C = result & 0x100 ? 1 : 0;
	FLAG_C = (A == 0x00) ? 0 : 1;
	
	A = (uint8_t) result;
	cpu->ts = 8;
}
