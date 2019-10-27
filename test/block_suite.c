#include "block_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_block_suite(void) {
	cpu_init();
	return 0;
}

int clean_block_suite(void) {
	cpu_clean();
	return 0;
}


void ldi_test(void) {
	cpu_reset();
	HL = 0x1111;
	DE = 0x2222;
	BC = 0x0007;
	cpu->mem[0x1111] = 0x88;
	cpu->mem[0x2222] = 0x66;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0xA0;	// LDI
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x1112);
	CU_ASSERT(cpu->mem[0x1111] ==  0x88);
	CU_ASSERT(DE == 0x2223);
	CU_ASSERT(cpu->mem[0x2222] ==  0x88);
	CU_ASSERT(BC == 0x0006);
}
