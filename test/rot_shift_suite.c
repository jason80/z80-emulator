#include "rot_shift_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_rot_shift_suite(void) {
	cpu_init();
	return 0;
}
		
int clean_rot_shift_suite(void) {
	cpu_clean();
	return 0;
}

void rlca_test(void) {
	cpu_reset();
	A = 0x88; // 1000 1000
	cpu->mem[0] = 0x07;		// RLCA
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(A == 0x11);
}
