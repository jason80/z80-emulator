#include "cpu_suite.h"

#include <CUnit/Basic.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_cpu_suite(void) {
	cpu_init();
	return 0;
}

int clean_cpu_suite(void) {
	cpu_clean();
	return 0;
}

void endian_test(void) {
	word_t reg;
	opcode_t opcode;
	
	reg.h = 0xA6;
	reg.l = 0x32;
	
	CU_ASSERT(reg.word == 0xA632);
	
	opcode.byte = 0x95;		// 10 010 101
	
	CU_ASSERT(opcode.x == 2);
	CU_ASSERT(opcode.y == 2);
	CU_ASSERT(opcode.z == 5);
	
	CU_ASSERT(opcode.q == 0);
	CU_ASSERT(opcode.p == 1);
}

void register_test(void) {
	
	cpu_reset();
	
	BC = 0x8834;
	DE = 0x1221;
	HL = 0x4FA4;
	
	CU_ASSERT(B == 0x88);
	CU_ASSERT(C == 0x34);
	CU_ASSERT(D == 0x12);
	CU_ASSERT(E == 0x21);
	CU_ASSERT(H == 0x4F);
	CU_ASSERT(L == 0xA4);
	
}

void fetch_test(void) {
	
	cpu_reset();
	
	cpu->mem[0] = 0x21;
	cpu->mem[1] = 0xAA;
	cpu->mem[2] = 0xBB;
	
	cpu_fetch();
	cpu_fetch();
	cpu_fetch();
	
	CU_ASSERT(IR == 0x21);
	CU_ASSERT(BR == 0xBBAA);
	CU_ASSERT(PC == 3);
}
