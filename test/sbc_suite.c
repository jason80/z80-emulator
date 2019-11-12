#include "sbc_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_sbc_suite(void) {
	cpu_init();
	return 0;
}

int clean_sbc_suite(void) {
	cpu_clean();
	return 0;
}

void sbc_A_r_test() {
	cpu_reset();
	
	A = 1;
	L = 255; // -1
	
	cpu->mem[0] = 0x9D; // SBC, A, L
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 2);
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(FLAG_PV == 0);
}
