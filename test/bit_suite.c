#include "bit_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_bit_suite(void) {
	cpu_clean();
	return 0;
}

void bit_b_r_test(void) {
	cpu_reset();
	B = 0xFB;	// 1111 1011 bit 2
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0x50;	// BIT 2, B  (01 010 000)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_N == 0);
}
