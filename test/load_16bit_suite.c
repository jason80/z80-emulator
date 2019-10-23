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

void ld_IX_IY_nn(void) {
	cpu_reset();
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x21; // LD IX, 45A2h
	cpu->mem[2] = 0xA2;
	cpu->mem[3] = 0x45;
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0x21; // LD IY, 3040h
	cpu->mem[6] = 0x40;
	cpu->mem[7] = 0x30;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(IX == 0x45A2);
	CU_ASSERT(IY == 0x3040);
	
}
