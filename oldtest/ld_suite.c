#include "ld_suite.h"

#include "../core/cpu.h"
#include "../core/execute.h"

#include <CUnit/CUnit.h>

int init_ld_suite(void) {
	cpu_init();
	return 0;
}

int clean_ld_suite(void) {
	cpu_clean();
	return 0;
}

void ld_8_immediate_test(void) {
	cpu_reset();
	
	HL = 0xAA34;
	
	cpu->mem[0] = 0x3E; // ld a, 0x34
	cpu->mem[1] = 0x34;
	cpu->mem[2] = 0x16; // ld d, 0x10
	cpu->mem[3] = 0x10;
	cpu->mem[4] = 0x1E; // ld e, 0x89
	cpu->mem[5] = 0x89;
	cpu->mem[6] = 0x36; // ld (hl), 0x44
	cpu->mem[7] = 0x44;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x34);
	CU_ASSERT(D == 0x10);
	CU_ASSERT(E == 0x89);
	CU_ASSERT(cpu->mem[0xAA34] == 0x44);
}

void ld_16_immediate_test(void) {
	cpu_reset();
	cpu->mem[0] = 0x11; // ld de, 0x45AA
	cpu->mem[1] = 0xAA;
	cpu->mem[2] = 0x45;
	cpu->mem[3] = 0x21; // ld hl, 0x2320
	cpu->mem[4] = 0x20;
	cpu->mem[5] = 0x23;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(DE == 0x45AA);
	CU_ASSERT(HL == 0x2320);
}

void ld_indirect_reg_test(void) {
	cpu_reset();
	BC = 0x4C21;
	DE = 0x2364;
	HL = 0xCCAA;
	A = 0x88;
	
	cpu->mem[0] = 0x02; // ld (bc), a
	cpu->mem[1] = 0x12; // ld (de), a
	cpu->mem[2] = 0x22; // ld (0x3B78), hl
	cpu->mem[3] = 0x78;
	cpu->mem[4] = 0x3B;
	cpu->mem[5] = 0x32; // ld (0x1011), a
	cpu->mem[6] = 0x11;
	cpu->mem[7] = 0x10;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(PC == 8);
	CU_ASSERT(cpu->mem[0x4C21] == 0x88);
	CU_ASSERT(cpu->mem[0x2364] == 0x88);
	
	CU_ASSERT(cpu->mem[0x3B78] == 0xAA);
	CU_ASSERT(cpu->mem[0x3B79] == 0xCC);
	
	CU_ASSERT(cpu->mem[0x1011] == 0x88);
}

void ld_reg_indirect_test(void) {
	cpu_reset();
	
	BC = 0xF345;
	DE = 0xBACE;
	cpu->mem[0xF345] = 0xB2;
	cpu->mem[0xBACE] = 0x56;
	cpu->mem[0x20D0] = 0x10;
	cpu->mem[0xBB33] = 0x76;
	
	cpu->mem[0] = 0x0A; // ld a, (bc)
	cpu->mem[1] = 0x1A; // ld a, (de)
	cpu->mem[2] = 0x2A; // ld hl, (20D0)
	cpu->mem[3] = 0xD0;
	cpu->mem[4] = 0x20;
	cpu->mem[5] = 0x3A; // ld a, (BB33)
	cpu->mem[6] = 0x33;
	cpu->mem[7] = 0xBB;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0xB2);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x56);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x10);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x76);
}

void ld_8_reg_test(void) {
	cpu_reset();
	
	A = 20; B = 60; H = 32;
	
	cpu->mem[0] = 0x57; // ld d, a
	cpu->mem[1] = 0x48; // ld c, b
	cpu->mem[2] = 0x6C; // ld l, h
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(D == 20);
	CU_ASSERT(C == 60);
	CU_ASSERT(L == 32);
	
}

void ld_sp_hl_test(void) {
	cpu_reset();
	HL = 43;
	
	cpu->mem[0] = 0xF9; // ld sp, hl
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(SP == 43);
}

void ld_indirect_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0xD4B5] = 0x83;
	cpu->mem[0xD4B6] = 0x54;
	
	cpu->mem[0] = 0xED; // Prefix
	cpu->mem[1] = 0x5B; // ld de, (0xD4B5)
	cpu->mem[2] = 0xB5;
	cpu->mem[3] = 0xD4;
	
	cpu->mem[4] = 0xED;
	cpu->mem[5] = 0x53;	// ld (0x4544), de
	cpu->mem[6] = 0x44;
	cpu->mem[7] = 0x45;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(DE == 0x5483);
	CU_ASSERT(cpu->mem[0x4544] == 0x83);
	CU_ASSERT(cpu->mem[0x4545] == 0x54);
}

void ld_a_i_r_test(void) {
	cpu_reset();
	A = 0x22;
	I = 0xA3;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x4F; // ld r, a
	
	cpu->mem[2] = 0xED;
	cpu->mem[3] = 0x57; // ld a, i
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(R == 0x22);
	CU_ASSERT(A == 0xA3);
	CU_ASSERT(I == 0xA3);
}

void push_pop_test(void) {
	cpu_reset();
	SP = 0;
	
	AF = 0x23AB;
	
	cpu->mem[0] = 0xF5; // PUSH AF
	cpu->mem[1] = 0xC1;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0x23AB);
}

void ld_8_indirect_relative_test(void) {
	cpu_reset();
	
	IX = 0x0020;
	IY = 0x3440;
	cpu->mem[0x0025] = 0x3B;
	cpu->mem[0x3480] = 0xAC;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x7E; // LD A, (IX + 5)
	cpu->mem[2] = 0x05;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x56; // LD D, (IY + 40)
	cpu->mem[5] = 0x40;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x3B);
	CU_ASSERT(D == 0xAC);
}

void ld_indirect_relative_8_test(void) {
	cpu_reset();
	IX = 0x4545;
	IY = 0x034B;
	H = 0x04;
	C = 0x11;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x74;	// LD (IX + 0x12), H
	cpu->mem[2] = 0x12;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x71; // LD (IY + 0x0A), C
	cpu->mem[5] = 0x0A;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x4545 + 0x12] == 0x04);
	CU_ASSERT(cpu->mem[0x034B + 0x0A] == 0x11);
}

