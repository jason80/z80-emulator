#include "exchange.h"

#include "cpu.h"

void ex_de_hl(void) {
	uint16_t tmp;
	tmp = DE;
	DE = HL;
	HL = tmp;
	cpu->ts = 4;
}

void ex_sp_hl(void) {
	word_t tmp;
	tmp.l = cpu->mem[SP];
	tmp.h = cpu->mem[SP + 1];
	
	cpu->mem[SP] = L;
	cpu->mem[SP + 1] = H;
	
	HL = tmp.word;
	
	cpu->ts = 19;
}

void ex_af_af(void) {
	uint16_t tmp;
	tmp = AF;
	AF = cpu->alter.af.word;
	cpu->alter.af.word = tmp;
	cpu->ts = 4;
}

void exx(void) {
	uint16_t tmp;
	// BC
	tmp = BC;
	BC = cpu->alter.bc.word;
	cpu->alter.bc.word = tmp;
	
	// BC
	tmp = DE;
	DE = cpu->alter.de.word;
	cpu->alter.de.word = tmp;
	
	// HL
	tmp = HL;
	HL = cpu->alter.hl.word;
	cpu->alter.hl.word = tmp;
	
	cpu->ts = 4;
}
