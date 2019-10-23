#include "load_16bit_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_load_16bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_load_16bit_suite(void) {
	cpu_clean();
	return 0;
}

void ld_rr_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0x21; // LD HL, 5432h
	cpu->mem[1] = 0x32;
	cpu->mem[2] = 0x54;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x5432);
}
