#include "search.h"

#include "../core/cpu.h"

uint16_t compare(int inc);

void cpi(void) {
	compare(1);
	cpu->ts = 16;
}

void cpir(void) {
	
	if (compare(1) == 0 || BC == 0) {
		cpu->ts = 16;
	} else {
		PC -= 2;
		cpu->ts = 21;
	}
}

void cpd(void) {
	compare(0);
	cpu->ts = 16;
}

void cpdr(void) {
	if (compare(0) == 0 || BC == 0) {
		cpu->ts = 16;
	} else {
		PC -= 2;
		cpu->ts = 21;
	}
}

uint16_t compare(int inc) {
	uint16_t result;
	uint8_t num1, num2;
	result = A - cpu->mem[HL];
	
	if (inc)
		HL ++;
	else HL --;
	
	BC --;
	
	FLAG_S = (result < 0) ? 1 : 0;
	FLAG_Z = (result == 0) ? 1 : 0;
	
	num1 = A & 0x0F;
	num2 = cpu->mem[HL] & 0x0F;
	
	FLAG_H = (num1 - num2) & 0x10 ? 1 : 0;
	
	FLAG_PV = (BC != 0) ? 1 : 0;
	FLAG_N = 1;
	
	return result;
}
