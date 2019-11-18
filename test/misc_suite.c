#include "misc_suite.h"

#include <CUnit/CUnit.h>
#include "../core/cpu.h"
#include "../core/execute.h"

int init_misc_suite(void) {
	cpu_init();
	return 0;
}

int clean_misc_suite(void) {
	cpu_clean();
	return 0;
}

void daa_test(void) {
	cpu_reset();
	A = 0x15;
	
	cpu->mem[0] = 0xC6; // ADD A, 27h
	cpu->mem[1] = 0x27;
	cpu->mem[2] = 0x27; // DAA
	
	cpu->mem[3] = 0xD6; // SUB 59h
	cpu->mem[4] = 0x59;
	cpu->mem[5] = 0x27; // DAA
	
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x42); // 27 + 15 = 42
	
	A = 0x96;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x37); // 96 - 59 = 37
}

void cpl_test(void) {
	cpu_reset();
	
	A = 0xB4; // 10110100
	
	cpu->mem[0] = 0x2F; // CPL
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x4B); // 01001011
}

void neg_test(void) {
	cpu_reset();
	
	A = 0x98;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x44;	// NEG
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x68);
}

void ccf_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0x3F;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_N == 0);
}
