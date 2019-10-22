#include "cpu.h"

#include <malloc.h>

cpu_t* cpu;

uint8_t fetch_byte(void);

void cpu_init(void) {
	cpu = (cpu_t*) malloc(sizeof(cpu_t));
	cpu_reset();
}

void cpu_reset(void) {
	unsigned int i;
	
	// Main registers
	A = 0; F = 0;
	BC = 0; DE = 0; HL = 0;
	I = 0; R = 0;
	IX = 0; IY = 0;
	PC = 0; SP = 0;
	
	// Alternate registers
	cpu->alter.af.word = 0;
	cpu->alter.bc.word = 0;
	cpu->alter.de.word = 0;
	cpu->alter.hl.word = 0;
	
	// Internal and memory
	BR = 0; IR = 0; ADR = 0;
	cpu->fetch_status = FETCH_INST;
	for (i = 0; i < 0x10000; i ++) {
		cpu->mem[i] = 0;
	}
}

void cpu_clean(void) {
	free(cpu);
}

void cpu_fetch(void) {
	switch (cpu->fetch_status) {
	case FETCH_INST:
		IR = fetch_byte();
		BRH = IR;
		break;
	case FETCH_L:
		BRL = fetch_byte();
		break;
	case FETCH_H:
		BRH = fetch_byte();
		break;
	}
	
	cpu->fetch_status ++;
}

uint8_t fetch_byte(void) {
	ADR = PC;
	PC ++;
	return DATA;
}
