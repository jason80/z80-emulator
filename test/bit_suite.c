#include "bit_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_bit_suite(void) {
	cpu_clean();
	return 0;
}

void bit_b_r_test(void) {
	cpu_reset();
	B = 0xFB;	// 1111 1011 bit 2
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0x50;	// BIT 2, B  (01 010 000)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_N == 0);
}

void bit_b_hl_test(void) {
	cpu_reset();
	HL = 0x4444;
	cpu->mem[0x4444] = 0x10; // 0001 0000
	
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0x66;	// BIT 2, (HL)  (01 100 110)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_N == 0);
}

void bit_b_IX_IY_relative_test(void) {
	cpu_reset();
	
	IX = 0x2000;
	IY = 0x3000;
	
	cpu->mem[0x2004] = 0x40; // 0100 0000
	cpu->mem[0x3002] = 0xFE; // 1111 1110
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0xCB;
	cpu->mem[2] = 0x04;
	cpu->mem[3] = 0x76; // BIT 6, (IX + 4h)		(01 110 110)
	
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0xCB;
	cpu->mem[6] = 0x02;
	cpu->mem[7] = 0x46; // BIT 0, (IY + 2h)		(01 000 110)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_N == 0);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 1);
	CU_ASSERT(FLAG_H == 1);
	CU_ASSERT(FLAG_N == 0);
}

void set_b_r_test(void) {
	cpu_reset();
	A = 0;
	
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0xE7;	// SET 4, A		(11 100 111)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x10);	
}

void set_b_hl_test(void) {
	cpu_reset();
	HL = 0x3000;
	cpu->mem[0x3000] = 0x00;
	
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0xE6;	// SET 4, (HL)      (11 100 110)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x3000] == 0x10);
}

void set_b_IX_IY_relative_test(void) {
	cpu_reset();
	IX = 0x2000;
	IY = 0x3400;
	cpu->mem[0x2003] = 0;
	cpu->mem[0x340A] = 0;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0xCB;
	cpu->mem[2] = 0x03;
	cpu->mem[3] = 0xC6;	// SET 0, (IX + 3h)
	
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0xCB;
	cpu->mem[6] = 0x0A;
	cpu->mem[7] = 0xC6;	// SET 0, (IY + Ah)
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x2003] == 1);
	CU_ASSERT(cpu->mem[0x340A] == 1);
}

void reset_b_r_test(void) {
	cpu_reset();
	
	B = 0xFF;	// (1111 1111)
	
	cpu->mem[0] = 0xCB;
	cpu->mem[1] = 0xB0;	// RES 6, B
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(B == 0xBF);	// (1011 1111)
	
}
