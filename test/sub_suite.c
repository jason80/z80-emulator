#include "sub_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_sub_suite(void) {
	cpu_init();
	return 0;
}

int clean_sub_suite(void) {
	cpu_clean();
	return 0;
}

void sub_A_r_test(void) {
	cpu_reset();
	
	A = 0x29;
	D = 0x11;
	
	cpu->mem[0] = 0x92;	// SUB D
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x18);
}
