#include "jump_suite.h"

#include <CUnit/CUnit.h>
#include "../core/cpu.h"
#include "../core/execute.h"

#include "../core/mem_loader.h"

int init_jump_suite(void) {
	cpu_init();
	return 0;
}

int clean_jump_suite(void) {
	cpu_clean();
	return 0;
}

void jp_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0xC3;
	cpu->mem[1] = 0x02;
	cpu->mem[2] = 0x40;			// JP 4002h
	
	cpu->mem[0x4002] = 0x3E;
	cpu->mem[0x4003] = 0x44;	// LD A, 44h
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x44);
}

void jp_cc_nn_test(void) {
	cpu_reset();
	FLAG_C = 1;
	cpu->mem[0x1520] = 0x03;
	
	cpu->mem[0] = 0xDA;
	cpu->mem[1] = 0x20;
	cpu->mem[2] = 0x15;	// JP C, 1520h
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[PC] == 0x03);
}

void jr_e_test(void) {
	cpu_reset();
	
	PC = 480;
	
	cpu->mem[480] = 0x18;	// JR +5
	cpu->mem[481] = 0x03;
	
	cpu->mem[485] = 0x18;	// JR -10
	cpu->mem[486] = 0xF4;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 485);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 475);
}

void jr_C_e_test(void) {
	cpu_reset();
	FLAG_C = 1;
	PC = 0x480;
	
	cpu->mem[0x480] = 0x38; // JR C, -4
	cpu->mem[0x481] = 0xFA; // -6
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x47C);
}

void jr_NC_e_test(void) {
	cpu_reset();
	
	FLAG_C = 0;
	PC = 0x480;
	
	cpu->mem[0x480] = 0x30; // JR NC, -4
	cpu->mem[0x481] = 0xFA; // -6
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x47C);
}

void jr_Z_e_test(void) {
	cpu_reset();
	
	FLAG_Z = 1;
	PC = 0x300;
	
	cpu->mem[0x300] = 0x28; // JR Z, +5
	cpu->mem[0x301] = 0x03; // 3
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x305);
}

void jr_NZ_e_test(void) {
	cpu_reset();
	
	FLAG_Z = 0;
	PC = 0x480;
	
	cpu->mem[0x480] = 0x20; // JR NZ, +4
	cpu->mem[0x481] = 0xFA; // -6
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x47C);
}

void jp_HL_test(void) {
	cpu_reset();
	
	PC = 0x1000;
	HL = 0x4800;
	
	cpu->mem[0x1000] = 0xE9; // JP (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x4800);
}

void jp_IX_IY_test(void) {
	cpu_reset();
	
	PC = 0x2000;
	IX = 0x2200;
	IY = 0x4400;
	
	cpu->mem[0x2000] = 0xDD; // JP (IX)
	cpu->mem[0x2001] = 0xE9;
	
	cpu->mem[0x2200] = 0xFD; // JP (IY)
	cpu->mem[0x2201] = 0xE9;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x2200);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 0x4400);
}

void djnz_test(void) {
	cpu_reset();
	
	load_memory(0, "../test/asm/djnz.bin");
	
	while (!cpu->halt) {
		cpu_fetch();
		cpu_execute();
	}
	
	CU_ASSERT(cpu->mem[0x2000] == 'H');
	CU_ASSERT(cpu->mem[0x2001] == 'e');
	CU_ASSERT(cpu->mem[0x2002] == 'l');
	CU_ASSERT(cpu->mem[0x2003] == 'l');
	CU_ASSERT(cpu->mem[0x2004] == 'o');
	CU_ASSERT(cpu->mem[0x2005] == 0x0D);
}
