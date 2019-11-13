#include "cp_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_cp_suite(void) {
	cpu_init();
	return 0;
}

int clean_cp_suite(void) {
	cpu_clean();
	return 0;
}

void cp_A_r_test(void) {
	cpu_reset();
	A = 32;
	H = 32;
	
	cpu->mem[0] = 0xBC; // CP H
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_PV == 0);
}
