#include "exchange_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_exchange_suite(void) {
	cpu_init();
	return 0;
}

int clean_exchange_suite(void) {
	cpu_clean();
	return 0;
}

void ex_de_hl_test(void) {
	cpu_reset();
	DE = 0x2822;
	HL = 0x499A;
	
	cpu->mem[0] = 0xEB; // LD DE, HL
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(DE == 0x499A);
	CU_ASSERT(HL == 0x2822);
}

void ex_af_af_test(void) {
	cpu_reset();
	AF = 0x9900;
	cpu->alter.af.word = 0x5944;
	
	cpu->mem[0] = 0x08;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(AF == 0x5944);
	CU_ASSERT(cpu->alter.af.word == 0x9900);
}

void exx_test(void) {
	
	cpu_reset();
	
	BC = 0x445A;
	DE = 0x3DA2;
	HL = 0x8859;
	cpu->alter.bc.word = 0x0988;
	cpu->alter.de.word = 0x9300;
	cpu->alter.hl.word = 0x00E7;
	
	cpu->mem[0] = 0xD9;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0x0988);
	CU_ASSERT(DE == 0x9300);
	CU_ASSERT(HL == 0x00E7);
	CU_ASSERT(cpu->alter.bc.word == 0x445A);
	CU_ASSERT(cpu->alter.de.word == 0x3DA2);
	CU_ASSERT(cpu->alter.hl.word == 0x8859);
}
