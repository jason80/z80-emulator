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
