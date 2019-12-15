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
