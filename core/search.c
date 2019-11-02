#include "search.h"

#include "../core/cpu.h"

void cpi(void) {
	int16_t result;
	uint8_t num1, num2;
	result = A - cpu->mem[HL];
	
	HL ++; BC --;
	
	FLAG_S = (result < 0) ? 1 : 0;
	FLAG_Z = (result == 0) ? 1 : 0;
	
	//FLAG_H = ((A & 0x0F) - (cpu->mem[HL] & 0x0F)) & 0x10;
	num1 = A & 0x0F;
	num2 = cpu->mem[HL] & 0x0F;
	
	FLAG_H = (num1 - num2) & 0x10 ? 1 : 0;
	
	FLAG_PV = (BC != 0) ? 1 : 0;
	FLAG_N = 1;
	
	cpu->ts = 16;
}

void cpir(void) {
	uint16_t result;
	uint8_t num1, num2;
	result = A - cpu->mem[HL];
	HL ++; BC --;
	
	FLAG_S = (result < 0) ? 1 : 0;
	FLAG_Z = (result == 0) ? 1 : 0;
	
	num1 = A & 0x0F;
	num2 = cpu->mem[HL] & 0x0F;
	
	FLAG_H = (num1 - num2) & 0x10 ? 1 : 0;
	
	FLAG_PV = (BC != 0) ? 1 : 0;
	FLAG_N = 1;
	
	if (result == 0 || BC == 0) {
		cpu->ts = 16;
	} else {
		PC -= 2;
		cpu->ts = 21;
	}
}
