#include "arithm_16bit_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_arithm_16bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_arithm_16bit_suite(void) {
	cpu_clean();
	return 0;
}

void add16_hl_rr_test(void) {
	cpu_reset();
	
	HL = 0x4242;
	DE = 0x1111;
	
	cpu->mem[0] = 0x19; // ADD HL, DE
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x5353);
}

void adc16_hl_rr_test(void) {
	cpu_reset();
	
	HL = 0x5437;
	BC = 0x2222;
	FLAG_C = 1;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x4A;	// ADC HL, BC
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x765A);
	CU_ASSERT(FLAG_C == 0);
}

void sbc16_hl_rr_test(void) {
	cpu_reset();
	
	HL = 0x9999;
	DE = 0x1111;
	FLAG_C = 1;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x52;	// SBC HL, BC
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x8887);
}
