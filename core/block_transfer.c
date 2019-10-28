#include "block_transfer.h"

#include "../core/cpu.h"

void transfer_de_hl(void);

void ldi(void) {
	transfer_de_hl();
	DE ++; HL ++; BC --;
	
	FLAG_H = 0;
	FLAG_N = 0;
	FLAG_PV = (BC != 0) ? 1 : 0;
	
	cpu->ts = 16;
}

void ldir(void) {
	ldi();
	if (BC == 0) {
		cpu->ts = 16;
	} else {
		PC -= 2;
		cpu->ts = 21;
	}
}

void ldd(void) {
	transfer_de_hl();
	DE --; HL --; BC --;
	
	FLAG_H = 0;
	FLAG_N = 0;
	FLAG_PV = (BC != 0) ? 1 : 0;
	
	cpu->ts = 16;
}

void lddr(void) {
	ldd();
	if (BC == 0) {
		cpu->ts = 16;
	} else {
		PC -= 2;
		cpu->ts = 21;
	}
}

void transfer_de_hl(void) {
	cpu->mem[DE] = cpu->mem[HL];
}
