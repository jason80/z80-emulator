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

void cpir_test(void) {
	cpu_reset();
	
	HL = 0x1111;
	A = 0xF3;
	BC = 0x0007;
	cpu->mem[0x1111] = 0x52;
	cpu->mem[0x1112] = 0x00;
	cpu->mem[0x1113] = 0xF3;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0xB1;
	
	while (PC < 2) {
		cpu_fetch(); cpu_execute();
	}
	
	CU_ASSERT(HL == 0x1114);
	CU_ASSERT(BC == 0x0004);
	CU_ASSERT(FLAG_PV == 1);
	CU_ASSERT(FLAG_Z = 1);
	
}

void cpd_test(void) {
	cpu_reset();
	
	HL = 0x1111;
	BC = 0x0001;
	A = 0x3B;
	cpu->mem[0x1111] = 0x3B;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0xA9;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0);
	CU_ASSERT(HL == 0x1110);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_PV == 0);
	
}

void cpdr_test(void) {
	cpu_reset();
	HL = 0x1118;
	BC = 0x0007;
	A = 0xF3;
	
	cpu->mem[0x1118] = 0x52;
	cpu->mem[0x1117] = 0x00;
	cpu->mem[0x1116] = 0xF3;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0xB9;
	
	do {
		cpu_fetch();
		cpu_execute();
	} while (FLAG_Z == 0);
	
	CU_ASSERT(HL == 0x1115);
	CU_ASSERT(BC == 0x0004);
	CU_ASSERT(FLAG_PV == 1);
	CU_ASSERT(FLAG_Z == 1);
	
}
