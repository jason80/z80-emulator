#include "add_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_add_suite() {
	cpu_init();
	return 0;
}

int clean_add_suite() {
	cpu_clean();
	return 0;
}

void add_A_r_test(void) {
	cpu_reset();
	A = 0x44;
	C = 0x11;
	B = 0x40;
	H = 0x80;
	
	cpu->mem[0] = 0x81;	// ADD A, C
	cpu->mem[1] = 0x80;	// ADD A, B
	cpu->mem[2] = 0x84;	// ADD A, H
	
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x55);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 0);
	CU_ASSERT(FLAG_C == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x95);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 1);
	CU_ASSERT(FLAG_C == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x015); // 0x115
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 1);
	CU_ASSERT(FLAG_C == 1);
}
