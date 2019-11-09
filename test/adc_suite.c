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

void adc_A_IX_IY_relative_test(void) {
	cpu_reset();
	A = 0x11;
	IX = 0x1000;
	IY = 0x2000;
	cpu->mem[0x1005] = 0x22;
	cpu->mem[0x2009] = 0x40;
	FLAG_C = 1;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x8E;	// ADC A, (IX + 5h)
	cpu->mem[2] = 0x05;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x8E;	// ADC A, (IY + 9h)
	cpu->mem[5] = 0x09;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x34);
	CU_ASSERT(FLAG_C == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x74);
	CU_ASSERT(FLAG_C == 0);
}

