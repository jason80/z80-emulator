#include "misc_suite.h"

#include <CUnit/CUnit.h>
#include "../core/cpu.h"
#include "../core/execute.h"

int init_misc_suite(void) {
	cpu_init();
	return 0;
}

int clean_misc_suite(void) {
	cpu_clean();
	return 0;
}

void daa_test(void) {
	cpu_reset();
	A = 0x15;
	
	cpu->mem[0] = 0xC6; // ADD A, 27h
	cpu->mem[1] = 0x27;
	cpu->mem[2] = 0x27; // DAA
	
	cpu->mem[3] = 0xD6; // SUB 59h
	cpu->mem[4] = 0x59;
	cpu->mem[5] = 0x27; // DAA
	
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x42); // 27 + 15 = 42
	
	A = 0x96;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x37); // 96 - 59 = 37
}
