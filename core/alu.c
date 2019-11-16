#include "alu.h"

#include "../core/cpu.h"

void add(uint8_t* reg8);
void adc(uint8_t* reg8);
void sub(uint8_t* reg8);
void sbc(uint8_t* reg8);

void cp(uint8_t* reg8);

void parity_check(uint8_t*);
void logic_flag_check(uint8_t*);

void alu(uint8_t operation, uint8_t* reg8) {
	switch(operation) {
	case 0:		// ADD
		add(reg8); cpu->ts = 4;
		break;
	case 1:		// ADC
		adc(reg8); cpu->ts = 4;
		break;
	case 2:		// SUB
		sub(reg8); cpu->ts = 4;
		break;
	case 3:		// SBC
		sbc(reg8); cpu->ts = 4;
		break;
	case 4:		// AND
		A &= *reg8;
		logic_flag_check(&A);
		cpu->ts = 4;
		break;
	case 5:		// XOR
		A ^= *reg8;
		logic_flag_check(&A);
		cpu->ts = 4;
		break;
	case 6:		// OR
		A |= *reg8;
		logic_flag_check(&A);
		cpu->ts = 4;
		break;
	case 7:		// CP
		cp(reg8); cpu->ts = 4;
		break;
	}
}

void alu_n(uint8_t operation) {
	
	cpu_fetch();	// Fetch n
	
	switch(operation) {
	case 0:		// ADD
		add(&BRL); cpu->ts = 7;
		break;
	case 1:		// ADC
		adc(&BRL); cpu->ts = 7;
		break;
	case 2:		// SUB
		sub(&BRL); cpu->ts = 7;
		break;
	case 3:		// SBC
		sbc(&BRL); cpu->ts = 7;
		break;
	case 4:		// AND
		A &= BRL;
		logic_flag_check(&A);
		cpu->ts = 7;
		break;
	case 5:		// XOR
		A ^= BRL;
		logic_flag_check(&A);
		cpu->ts = 7;
		break;
	case 6:		// OR
		A |= BRL;
		logic_flag_check(&A);
		cpu->ts = 7;
		break;
	case 7:		// CP
		cp(&BRL); cpu->ts = 7;
		break;
	}
}

void alu_indirect(uint8_t operation, uint16_t* reg16) {
	cpu_fetch();	// Fetch n
	
	switch(operation) {
	case 0:		// ADD
		add(&cpu->mem[*reg16 + BRL]); cpu->ts = 19;
		break;
	case 1:		// ADC
		adc(&cpu->mem[*reg16 + BRL]); cpu->ts = 19;
		break;
	case 2:		// SUB
		sub(&cpu->mem[*reg16 + BRL]); cpu->ts = 19;
		break;
	case 3:		// SBC
		sbc(&cpu->mem[*reg16 + BRL]); cpu->ts = 19;
		break;
	case 4:		// AND
		A &= cpu->mem[*reg16 + BRL];
		logic_flag_check(&A);
		cpu->ts = 19;
		break;
	case 5:		// XOR
		A ^= cpu->mem[*reg16 + BRL];
		logic_flag_check(&A);
		cpu->ts = 19;
		break;
	case 6:		// OR
		A |= cpu->mem[*reg16 + BRL];
		logic_flag_check(&A);
		cpu->ts = 19;
		break;
	case 7:		// CP
		cp(&cpu->mem[*reg16 + BRL]); cpu->ts = 19;
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
}

void adc(uint8_t* reg8) {
	uint16_t result = A + *reg8 + FLAG_C;
	
	FLAG_S = result < 0 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	
	FLAG_H = (((A & 0x0F) + (*reg8 & 0x0F) + FLAG_C) & 0x10) > 0 ? 1 : 0;
	
	// Overflow pv
	FLAG_PV = 0;
	if ((A & 0x80) == (*reg8 & 0x80))
		if ((A & 0x80) != (result & 0x80))
			FLAG_PV = 1;
	
	FLAG_C = result & 0x100 ? 1 : 0;
	
	A = (uint8_t) result;
}

void sub(uint8_t* reg8) {
	uint16_t result = A - *reg8;
	
	FLAG_S = result < 0 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	
	FLAG_H = (((A & 0x0F) - (*reg8 & 0x0F)) & 0x10) > 0 ? 1 : 0;
	
	// Overflow pv
	FLAG_PV = 0;
	if ((A & 0x80) != (*reg8 & 0x80))
		if ((A & 0x80) != (result & 0x80))
			FLAG_PV = 1;
	
	FLAG_C = result & 0x100 ? 1 : 0;
	
	A = (uint8_t) result;
}

void sbc(uint8_t* reg8) {
	uint16_t result = A - *reg8 - FLAG_C;
	
	FLAG_S = result < 0 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	
	FLAG_H = (((A & 0x0F) - (*reg8 & 0x0F) - FLAG_C) & 0x10) > 0 ? 1 : 0;
	
	// Overflow pv
	FLAG_PV = 0;
	if ((A & 0x80) != (*reg8 & 0x80))
		if ((A & 0x80) != (result & 0x80))
			FLAG_PV = 1;
	
	FLAG_C = result & 0x100 ? 1 : 0;
	
	A = (uint8_t) result;
}

void cp(uint8_t* reg8) {
	uint16_t result = A - *reg8;
	
	FLAG_S = result < 0 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	
	FLAG_H = (((A & 0x0F) - (*reg8 & 0x0F)) & 0x10) > 0 ? 1 : 0;
	
	// Overflow pv
	FLAG_PV = 0;
	if ((A & 0x80) != (*reg8 & 0x80))
		if ((A & 0x80) != (result & 0x80))
			FLAG_PV = 1;
	
	FLAG_C = result & 0x100 ? 1 : 0;
}

void inc(uint8_t* reg8) {
	uint8_t result = *reg8 + 1;
	FLAG_S = result & 0x80 ? 1 : 0;
	FLAG_Z = result == 0 ? 1 : 0;
	
	FLAG_H = (((A & 0x0F) + (*reg8 & 0x0F)) & 0x10) > 0 ? 1 : 0;
	FLAG_PV = result == 0x80 ? 1 : 0;
	FLAG_N = 0;
	*reg8 = result;
	cpu->ts = 4;
}

void inc_relative(uint16_t reg16) {
	
	cpu_fetch();
	inc(&cpu->mem[reg16 + BRL]);
	
	cpu->ts = 23;
	
}

void parity_check(uint8_t* reg8) {
	uint16_t p;
	uint8_t add = 0;
	
	for (p = 1; p <= 128; p *= 2) {
		add += (*reg8 & p) ? 1 : 0;
	}
	
	FLAG_PV = (add % 2 == 0) ? 1 : 0;
}

void logic_flag_check(uint8_t* reg8) {
	FLAG_S = (*reg8 & 0x80) ? 1 : 0;
	FLAG_Z = (*reg8 == 0) ? 1 : 0;
	FLAG_H = 1;
	parity_check(reg8);
	FLAG_N = 0;
	FLAG_C = 0;
}
