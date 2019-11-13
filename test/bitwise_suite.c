#include "bitwise_suite.h"

#include "CUnit/CUnit.h"

#include "../core/cpu.h"
#include "../core/execute.h"

int init_bitwise_suite(void) {
	cpu_init();
	return 0;
}

int clean_bitwise_suite(void) {
	cpu_clean();
	return 0;
}

void and_test(void) {
	cpu_reset();
	
	A = 0xC3; // 1100 0011
	B = 0x7B; // 0111 1011
	
	cpu->mem[0] = 0xA0; // AND B
	cpu->mem[1] = 0xE6; // AND BCh
	cpu->mem[2] = 0xBC; // 1011 1100
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x43); // 0100 0011
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x00);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_PV == 1);
}

void xor_test(void) {
	cpu_reset();
	
	A = 0x96; // 1001 0110
	HL = 0x2333;
	cpu->mem[0x2333] = 0x5D; // 0101 1101
	
	cpu->mem[0] = 0xAE; // OR (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0xCB); // 1100 1011
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 0);
}

void or_test(void) {
	cpu_reset();
	
	A = 0x12; // 0001 0010
	IX = 0x2457;
	cpu->mem[0x245A] = 0x48; // 0100 1000
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0xB6; // OR (IX + 3)
	cpu->mem[2] = 0x03;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x5A); // 0101 1010
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 1);
}
