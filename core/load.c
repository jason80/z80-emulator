#include "load.h"

#include "cpu.h"

void ld_8bit_n(uint8_t* reg8) { ////////
	cpu_fetch();
	*reg8 = BRL;
	cpu->ts = 7;
}

void ld_8bit_indirect_relative(uint8_t* reg8, uint16_t adr) {
	cpu_fetch();
	union {
		uint8_t uns;
		int8_t sig;
	} convert;
	
	convert.uns = BRL;
	
	*reg8 = cpu->mem[adr + convert.sig];
	cpu->ts = 19;
}

void ld_indirect_relative_8bit(uint16_t adr, uint8_t* reg8) {
	cpu_fetch();
	union {
		uint8_t uns;
		int8_t sig;
	} convert;
	convert.uns = BRL;
	
	cpu->mem[adr + convert.sig] = *reg8;
	cpu->ts = 19;
}

void ld_indirect_relative_n(uint16_t adr) {
	cpu_fetch(); cpu_fetch();
	union {
		uint8_t uns;
		int8_t sig;
	} convert;
	convert.uns = BRL;
	cpu->mem[adr + convert.sig] = BRH;
	cpu->ts = 19;
}

void ld_16bit_nn(uint16_t* reg16) { //////////////
	cpu_fetch(); cpu_fetch();
	*reg16 = BR; 
	if (reg16 == &IX || reg16 == &IY) cpu->ts = 14;
	else cpu->ts = 10;
}

void ld_indirect_8bit(uint16_t adr, uint8_t* reg8) { /////
	cpu->mem[adr] = *reg8;
	cpu->ts = 7;
}

void ld_indirect_nn_16bit(uint16_t* reg16) { ////////
	uint16_t tmp;
	cpu_fetch(); cpu_fetch();
	tmp = *reg16 & 0x00FF;
	cpu->mem[BR] = (uint8_t) tmp;
	tmp = *reg16 >> 8;
	cpu->mem[BR + 1] = (uint8_t) tmp;
	
	if (reg16 == &HL) cpu->ts = 16;
	else cpu->ts = 20;
}

void ld_indirect_nn_8bit(uint8_t* reg8) { /////
	cpu_fetch(); cpu_fetch();
	cpu->mem[BR] = *reg8;
	cpu->ts = 13;
}

void ld_8bit_indirect(uint8_t* reg8, uint16_t adr) { //////
	*reg8 = cpu->mem[adr];
	cpu->ts = 7;
}

void ld_16bit_indirect_nn(uint16_t* reg16) { ///////
	uint16_t tmp;
	cpu_fetch(); cpu_fetch();
	*reg16 = cpu->mem[BR];
	tmp = cpu->mem[BR + 1];
	tmp <<= 8;
	*reg16 |= tmp;
	
	if (reg16 == &HL) cpu->ts = 16;
	else cpu->ts = 20;
}

void ld_8bit_indirect_nn(uint8_t* reg8) { //////
	cpu_fetch(); cpu_fetch();
	*reg8 = cpu->mem[BR];
	cpu->ts = 13; 
}

void ld_8bit_8bit(uint8_t* reg1, uint8_t* reg2) { //////
	*reg1 = *reg2; cpu->ts = 4;
	if (reg2 == &I || reg2 == &R) { // LD A, R or LD A, I
		FLAG_S = (*reg2 & 0x80) ? 1 : 0;
		FLAG_Z = (*reg2 == 0) ? 1 : 0;
		FLAG_H = 0;
		// TODO: P/V contains contents of IFF2
		FLAG_N = 0;
		
		cpu->ts = 9;
	} else if (reg2 == &I || reg2 == &R) { // LD R, A or LD I, A
		cpu->ts = 9;
	}
}

void ld_sp_hl(void) {
	SP = HL;
	cpu->ts = 6;
}

void push(uint16_t* reg16) {
	uint16_t h = *reg16 >> 8;
	SP --;
	ADR = SP; DATA = (uint8_t) h;
	SP --;
	ADR = SP; DATA = *reg16 & 0xFF;
	cpu->ts = 11;
}

void pop(uint16_t* reg16) {
	uint16_t h;
	uint8_t l;
	ADR = SP;
	l = DATA; SP ++;
	ADR = SP;
	h = DATA; SP ++;
	
	h <<= 8;
	
	*reg16 = h | l;
	
	cpu->ts = 10;
}

