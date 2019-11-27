#include "rot_shift_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_rot_shift_suite(void) {
	cpu_init();
	return 0;
}
		
int clean_rot_shift_suite(void) {
	cpu_clean();
	return 0;
}

void rlca_test(void) {
	cpu_reset();
	A = 0x88; // 1000 1000
	cpu->mem[0] = 0x07;		// RLCA
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(A == 0x11);
}

void rla_test(void) {
	cpu_reset();
	A = 0x76; // 0111 0110
	FLAG_C = 1;
	cpu->mem[0] = 0x17;		// RLA
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 0);
	CU_ASSERT(A == 0xED);
}

void rrca_test(void) {
	cpu_reset();
	A = 0x11; // 0001 0001
	cpu->mem[0] = 0x0F;		// RRCA
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(A == 0x88);
}

void rra_test(void) {
	cpu_reset();
	A = 0xE1; // 1110 0001
	cpu->mem[0] = 0x1F;		// RRCA
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(A == 0x70);
}

void rlc_r_test(void) {
	cpu_reset();
	
	E = 0x88;
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0x03;	// RLC E
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(E == 0x11);
}

void rlc_hl_test(void) {
	cpu_reset();
	HL = 0x2828;
	cpu->mem[0x2828] = 0x88;
	
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0x06;	// RLC (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(cpu->mem[0x2828] == 0x11);
}

void rlc_IX_IY_test(void) {
	cpu_reset();
	IX = 0x1000;
	IY = 0x2000;
	cpu->mem[0x1022] = 0x88;
	cpu->mem[0x2002] = 0x44;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0xCB;
	cpu->mem[2] = 0x22;
	cpu->mem[3] = 0x06;		// RLC (IX + 22h)
	
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0xCB;
	cpu->mem[6] = 0x02;
	cpu->mem[7] = 0x06;		// RLC (IY + 02h)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 1);
	CU_ASSERT(cpu->mem[0x1022] == 0x11);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_C == 0);
	CU_ASSERT(cpu->mem[0x2002] == 0x88);
}

void rl_r_test(void) {
	cpu_reset();
	
	D = 0x8F;
	
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0x12;	// RL D
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(D == 0x1E);
	CU_ASSERT(FLAG_C == 1);
}

