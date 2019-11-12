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

void sub_A_n_test(void) {
	cpu_reset();
	
	A = 30;
	cpu->mem[0] = 0xD6;
	cpu->mem[1] = 30;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0);
	CU_ASSERT(FLAG_Z == 1);
}

void sub_A_HL_ref_test(void) {
	cpu_reset();
	A = 127;
	HL = 0x2323;
	cpu->mem[0x2323] = 129;
	
	cpu->mem[0] = 0x96;	// ADD A, (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 254);
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(FLAG_PV == 1);
}

void sub_A_IX_IY_relative_test(void) {
	cpu_reset();
	
	IX = 0x3444;
	IY = 0x4999;
	A = 1;
	cpu->mem[0x344A] = 127;
	cpu->mem[0x499A] = 130;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x96;	// SUB (IX + 6)
	cpu->mem[2] = 6;
	
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x96;	// SUB (IY + 1)
	cpu->mem[5] = 1;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 130);
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(FLAG_PV == 0);
	CU_ASSERT(FLAG_Z == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0);
	CU_ASSERT(FLAG_C == 0);
	CU_ASSERT(FLAG_PV == 0);
	CU_ASSERT(FLAG_Z == 1);
}
