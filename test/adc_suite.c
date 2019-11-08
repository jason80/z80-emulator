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

void adc_A_r_test(void) {
	cpu_reset();
	A = 128;
	C = 129;
	B = 255;
	FLAG_C = 1;
	
	cpu->mem[0] = 0x89;	// ADC A, B
	cpu->mem[1] = 0x88; // ADC A, C
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 2);
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(FLAG_PV == 1);
	
	A = 127;
	FLAG_C = 0;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 126);
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(FLAG_PV == 0);
}

void adc_A_n_test(void) {
	cpu_reset();
	A = 34;
	cpu->mem[0] = 0xCE; // ADC A, 33
	cpu->mem[1] = 0x21;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 67);
	
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

