#include "jump_suite.h"

#include <CUnit/CUnit.h>
#include "../core/cpu.h"
#include "../core/execute.h"

int init_jump_suite(void) {
	cpu_init();
	return 0;
}

int clean_jump_suite(void) {
	cpu_clean();
	return 0;
}

void jp_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0xC3;
	cpu->mem[1] = 0x02;
	cpu->mem[2] = 0x40;			// JP 4002h
	
	cpu->mem[0x4002] = 0x3E;
	cpu->mem[0x4003] = 0x44;	// LD A, 44h
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x44);
}
