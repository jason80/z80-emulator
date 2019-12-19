#include "jump.h"

#include "cpu.h"

void jump(void) {
	cpu_fetch();
	cpu_fetch();
	PC = BR;
	cpu->ts = 10;
}

void jump_conditional(int c) {
	if (c) jump();
}

void jump_relative(void) {
	
	union {
		uint8_t u;
		int8_t s;
	} val;
	
	cpu_fetch();
	val.u = BRL;
	
	PC += val.s;
	
	cpu->ts = 12;
}

void jr_c_rel(void) {
	if (FLAG_C) {
		jump_relative();
	} else {
		cpu_fetch();
		cpu->ts = 7;
	}
}

void jr_nc_rel(void) {
	if (!FLAG_C) {
		jump_relative();
	} else {
		cpu_fetch();
		cpu->ts = 7;
	}
}

void jr_z_rel(void) {
	if (FLAG_Z) {
		jump_relative();
	} else {
		cpu_fetch();
		cpu->ts = 7;
	}
}

void jr_nz_rel(void) {
	if (!FLAG_Z) {
		jump_relative();
	} else {
		cpu_fetch();
		cpu->ts = 7;
	}
}

void jump_reg(uint16_t* reg16) {
	PC = *reg16;
	if (reg16 == &HL) cpu->ts = 4;
	else if (reg16 == &IX || reg16 == &IY) cpu->ts = 8;
}

void djnz(void) {
	union {
		uint8_t u;
		int8_t s;
	} val;
	
	cpu_fetch();
	
	B --;
	if (B != 0) {
		val.u = BRL;
		PC += val.s;		
		cpu->ts = 13;
	} else
		cpu->ts = 8;
}
