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
	
	CU_ASSERT(FLAG_Z == 1); // A == H
	CU_ASSERT(FLAG_PV == 0);
	CU_ASSERT(FLAG_C == 0);
}

void cp_A_n_test(void) {
	cpu_reset();
	A = 120;
	
	cpu->mem[0] = 0xFE;	// CP 100
	cpu->mem[1] = 100;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0); // A != 100
	CU_ASSERT(FLAG_PV == 0); 
	CU_ASSERT(FLAG_C == 0);	// A > 100
}

void cp_A_HL_ref_test(void) {
	cpu_reset();
	A = 45;
	HL = 0xABC0;
	cpu->mem[0xABC0] = 96;
	
	cpu->mem[0] = 0xBE; // CP (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0); // A != (HL)
	CU_ASSERT(FLAG_PV == 0); 
	CU_ASSERT(FLAG_C == 1);	// A < (HL)
}
