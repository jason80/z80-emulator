#include "bitwise_suite.h"

#include "CUnit/CUnit.h"

#include "../core/cpu.h"
#include "../core/execute.h"

int init_bitwise_suite(void) {
	cpu_init();
	return 0;
}

int clean_bitwise_suite(void) {
	cpu_clean();
	return 0;
}

void and_test(void) {
	cpu_reset();
	
	A = 0xC3; // 1100 0011
	B = 0x7B; // 0111 1011
	
	cpu->mem[0] = 0xA0; // AND B
	cpu->mem[1] = 0xA1; // AND 5Eh
	cpu->mem[2] = 0x5E; // 1011 1100
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x43); // 0100 0011
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x00);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_PV == 1);
}
