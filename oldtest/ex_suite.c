#include "ex_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_ex_suite(void) {
	cpu_init();
	return 0;
}

int clean_ex_suite(void) {
	cpu_clean();
	return 0;
}

void ex_de_hl_test(void) {
	cpu_reset();
	DE = 0xF28A;
	HL = 0x1234;
	
	cpu->mem[0] = 0xEB; // EX DE, HL
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(DE == 0x1234);
	CU_ASSERT(HL == 0xF28A);
}

void ex_af_af_test(void) {
	cpu_reset();
	AF = 0x7834;
	cpu->alter.af.word = 0xABCD;
	
	cpu->mem[0] = 0x08; // EX AF, AF'
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(AF == 0xABCD);
	CU_ASSERT(cpu->alter.af.word == 0x7834);
}

void exx_test(void) {
	cpu_reset();
	BC = 0x445A;
	DE = 0x3DA2;
	HL = 0x8859;
	cpu->alter.bc.word = 0x0988;
	cpu->alter.de.word = 0x9300;
	cpu->alter.hl.word = 0x00E7;
	
	cpu->mem[0] = 0xD9;		// EXX
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0x0988);
	CU_ASSERT(DE == 0x9300);
	CU_ASSERT(HL == 0x00E7);
	
	CU_ASSERT(cpu->alter.bc.word == 0x445A);
	CU_ASSERT(cpu->alter.de.word == 0x3DA2);
	CU_ASSERT(cpu->alter.hl.word == 0x8859);
}

void ex_sp_hl_test(void) {
	cpu_reset();
	HL = 0xCCCC;
	SP = 0x2000;
	cpu->mem[0x2000] = 0x43;
	cpu->mem[0x2001] = 0xAB;
	
	cpu->mem[0] = 0xE3;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0xAB43);
	CU_ASSERT(cpu->mem[0x2000] == 0xCC);
	CU_ASSERT(cpu->mem[0x2001] == 0xCC);
}
