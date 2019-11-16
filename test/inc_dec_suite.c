#include "inc_dec_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_inc_dec_suite(void) {
	cpu_init();
	return 0;
}

int clean_inc_dec_suite(void) {
	cpu_clean();
	return 0;
}

void inc_r_test(void) {
	cpu_reset();
	A = 33;
	B = 0x7F;
	C = 0xFF;
	 
	cpu->mem[0] = 0x3C; // INC A
	cpu->mem[1] = 0x04; // INC B
	cpu->mem[2] = 0x0C; // INC C
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 34);
	CU_ASSERT(FLAG_S == 0);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_H == 0);
	CU_ASSERT(FLAG_PV == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(B == 0x80);
	CU_ASSERT(FLAG_S == 1);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_PV == 1);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(C == 0x00);
	CU_ASSERT(FLAG_S == 0);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_PV == 0);
}

void inc_hl_ref_test(void) {
	cpu_reset();
	
	HL = 0xAB00;
	cpu->mem[0xAB00] = 4;
	
	cpu->mem[0] = 0x34;	// INC (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0xAB00] == 5);
}

void inc_IX_IY_relative_test(void) {
	cpu_reset();
	IX = 0x2020;
	IY = 0x3220;
	cpu->mem[0x2030] = 0x34;
	cpu->mem[0x3240] = 0x50;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x34;	// INC (IX + 10h)
	cpu->mem[2] = 0x10;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x34;	// INC (IY + 20h)
	cpu->mem[5] = 0x20;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x2030] == 0x35);
	CU_ASSERT(cpu->mem[0x3240] == 0x51);
}

void dec_r_test(void) {
	cpu_reset();
	D = 0x2A;
	E = 0x80;
	
	cpu->mem[0] = 0x15; // DEC D
	cpu->mem[1] = 0x1D; // DEC E
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(D == 0x29);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(E == 0x7F);
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_PV == 1);
}

void dec_hl_ref_test(void) {
	cpu_reset();
	
	HL = 0x0123;
	cpu->mem[0x0123] = 1;
	
	cpu->mem[0] = 0x35; // DEC (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x0123] == 0);
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_PV == 0);
	
}

