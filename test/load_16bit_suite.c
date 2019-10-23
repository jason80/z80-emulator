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

void ld_hl_nn_ind_test(void) {
	cpu_reset();
	
	cpu->mem[0x4545] = 0x37;
	cpu->mem[0x4546] = 0xA1;
	
	cpu->mem[0] = 0x2A; // LD HL, (4545h)
	cpu->mem[1] = 0x45;
	cpu->mem[2] = 0x45;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0xA137);
}

void ld_dd_nn_ind_test(void) {
	cpu_reset();
	
	cpu->mem[0x2130] = 0x65;
	cpu->mem[0x2131] = 0x78;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x4B; // LD BC, (2130h)
	cpu->mem[2] = 0x30;
	cpu->mem[3] = 0x21;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0x7865);
}
