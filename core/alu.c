#include "alu.h"

#include "../core/cpu.h"

void add(uint8_t* reg8);

void alu(uint8_t operation, uint8_t* reg8) {
	switch(operation) {
	case 0:		// ADD
		add(reg8);
		break;
	case 1:		// ADC
		break;
	case 2:		// SUB
		break;
	case 3:		// SBC
		break;
	case 4:		// AND
		break;
	case 5:		// XOR
		break;
	case 6:		// OR
		break;
	case 7:		// CP
		break;
	}
}

void add(uint8_t* reg8) {
	uint16_t result = A + *reg8;
	
	FLAG_S = result < 0 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	
	FLAG_H = (((A & 0x0F) + (*reg8 & 0x0F)) & 0x10) > 0 ? 1 : 0;
	
	// Overflow pv
	FLAG_PV = 0;
	if ((A & 0x80) == (*reg8 & 0x80))
		if ((A & 0x80) != (result & 0x80))
			FLAG_PV = 1;
	
	FLAG_C = result & 0x100 ? 1 : 0;
	
	A = (uint8_t) result;
	cpu->ts = 4;
}
