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

void add16_IX_IY_rr_test(void) {
	cpu_reset();
	IX = 0x3333;
	IY = 0x2222;
	BC = 0x5555;
	DE = 0x1111;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x09;	// ADD IX, BC
	
	cpu->mem[2] = 0xFD;
	cpu->mem[3] = 0x19;	// ADD IY, DE
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(IX == 0x8888);
	CU_ASSERT(IY == 0x3333);
}

void inc16_test(void) {
	cpu_reset();
	HL = 0x1000;
	IX = 0x3300;
	IY = 0x2977;
	
	cpu->mem[0] = 0x23;	// INC HL
	cpu->mem[1] = 0xDD;
	cpu->mem[2] = 0x23; // INC IX
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x23; // INC IX
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x1001);
	CU_ASSERT(IX == 0x3301);
	CU_ASSERT(IY == 0x2978);
}

void dec16_test(void) {
	cpu_reset();
	HL = 0x1001;
	IX = 0x2006;
	IY = 0x7649;
	
	cpu->mem[0] = 0x2B;	// INC HL
	cpu->mem[1] = 0xDD;
	cpu->mem[2] = 0x2B; // INC IX
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x2B; // INC IX
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x1000);
	CU_ASSERT(IX == 0x2005);
	CU_ASSERT(IY == 0x7648);
}


