#include "search_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_search_suite(void) {
	cpu_init();
	return 0;
}

int clean_search_suite(void) {
	cpu_clean();
	return 0;
}

void cpi_test(void) {
	cpu_reset();
	
	HL = 0x1111;
	A = 0x3B;
	BC = 0x0001;
	cpu->mem[0x1111] = 0x3B;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0xA1;	// CPI
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0);
	CU_ASSERT(HL == 0x1112);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_PV == 0);
	CU_ASSERT(A == 0x3B);
	CU_ASSERT(cpu->mem[0x1111] == 0x3B);
	
}
