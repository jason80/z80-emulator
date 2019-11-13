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
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x43); // 0100 0011
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 0);
}
