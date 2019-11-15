#include "inc_dec_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_inc_dec_suite(void) {
	cpu_init();
	return 0;
}

int clean_inc_dec_suite(void) {
	cpu_clean();
	return 0;
}

void inc_r_test(void) {
	cpu_reset();
	A = 33;
	B = 0x7F;
	C = 0xFF;
	 
	cpu->mem[0] = 0x3C; // INC A
	cpu->mem[1] = 0x04; // INC B
	cpu->mem[2] = 0x0C; // INC C
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 34);
	CU_ASSERT(FLAG_S == 0);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_H == 0);
	CU_ASSERT(FLAG_PV == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(B == 0x80);
	CU_ASSERT(FLAG_S == 1);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_PV == 1);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(C == 0x00);
	CU_ASSERT(FLAG_S == 0);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_PV == 0);
}
