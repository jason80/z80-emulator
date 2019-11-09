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

void add_A_n_test(void) {
	cpu_reset();
	A = 0x23;
	
	cpu->mem[0] = 0xC6;		// ADD A, 33h
	cpu->mem[1] = 0x33;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x56);
}

void add_A_HL_ref_test(void) {
	cpu_reset();
	A = 0xA0;
	HL = 0x2323;
	cpu->mem[0x2323] = 0x08;
	
	cpu->mem[0] = 0x86;	// ADD A, (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0xA8);
	
}

void add_A_IX_IY_relative_test(void) {
	cpu_reset();
	A = 0x11;
	IX = 0x1000;
	IY = 0x2000;
	cpu->mem[0x1005] = 0x22;
	cpu->mem[0x2009] = 0x40;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x86;	// ADD A, (IX + 5h)
	cpu->mem[2] = 0x05;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x86;	// ADD A, (IY + 9h)
	cpu->mem[5] = 0x09;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x33);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x73);
}
