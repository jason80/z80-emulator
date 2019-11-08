#include "adc_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_adc_suite(void) {
	cpu_init();
	return 0;
}

int clean_adc_suite(void) {
	cpu_clean();
	return 0;
}

void adc_A_HL_ref_test(void) {
	A = 0x16;
	FLAG_C = 1;
	HL = 0x6666;
	cpu->mem[0x6666] = 0x10;
	
	cpu->mem[0] = 0x8E; // ADC A, (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x27);
}
