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

void ex_sp_hl_test(void) {
	cpu_reset();
	HL = 0x7012;
	SP = 0x8856;
	cpu->mem[0x8856] = 0x11;
	cpu->mem[0x8857] = 0x22;
	
	cpu->mem[0] = 0xE3;	// EX (SP), HL
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x8856] == 0x12);
	CU_ASSERT(cpu->mem[0x8857] == 0x70);
}

void ex_sp_IX_IY_test(void) {
	cpu_reset();
	IX = 0x3988;
	IY = 0x4567;
	SP = 0x0100;
	cpu->mem[0x0100] = 0x90;
	cpu->mem[0x0101] = 0x48;
	
	cpu->mem[0xA100] = 0x90;
	cpu->mem[0xA101] = 0x48;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0xE3; // EX (SP), IX
	cpu->mem[2] = 0xFD;
	cpu->mem[3] = 0xE3; // EX (SP), IY
	
	cpu_fetch();
	cpu_execute();
	
	SP = 0xA100;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x0100] == 0x88);
	CU_ASSERT(cpu->mem[0x0101] == 0x39);
	CU_ASSERT(cpu->mem[0xA100] == 0x67);
	CU_ASSERT(cpu->mem[0xA101] == 0x45);
	
}
