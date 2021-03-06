#include "load_16bit_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_load_16bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_load_16bit_suite(void) {
	cpu_clean();
	return 0;
}

void ld_rr_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0x21; // LD HL, 5432h
	cpu->mem[1] = 0x32;
	cpu->mem[2] = 0x54;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x5432);
}

void ld_IX_IY_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x21; // LD IX, 45A2h
	cpu->mem[2] = 0xA2;
	cpu->mem[3] = 0x45;
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0x21; // LD IY, 3040h
	cpu->mem[6] = 0x40;
	cpu->mem[7] = 0x30;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(IX == 0x45A2);
	CU_ASSERT(IY == 0x3040);
	
}

void ld_hl_nn_ind_test(void) {
	cpu_reset();
	
	cpu->mem[0x4545] = 0x37;
	cpu->mem[0x4546] = 0xA1;
	
	cpu->mem[0] = 0x2A; // LD HL, (4545h)
	cpu->mem[1] = 0x45;
	cpu->mem[2] = 0x45;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0xA137);
}

void ld_dd_nn_ind_test(void) {
	cpu_reset();
	
	cpu->mem[0x2130] = 0x65;
	cpu->mem[0x2131] = 0x78;
	
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x4B; // LD BC, (2130h)
	cpu->mem[2] = 0x30;
	cpu->mem[3] = 0x21;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(BC == 0x7865);
}

void ld_IX_IY_nn_ind_test(void) {
	cpu_reset();
	
	cpu->mem[0x6666] = 0x92;
	cpu->mem[0x6667] = 0xDA;
	
	cpu->mem[0x5555] = 0x32;
	cpu->mem[0x5556] = 0xAB;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x2A;	// LD IX, (0x6666)
	cpu->mem[2] = 0x66;
	cpu->mem[3] = 0x66;
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0x2A; // LD IY, (0x5555)
	cpu->mem[6] = 0x55;
	cpu->mem[7] = 0x55;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(IX == 0xDA92);
	CU_ASSERT(IY == 0xAB32);
}

void ld_nn_ind_hl_test(void) {
	cpu_reset();
	
	HL = 0x483A;
	
	cpu->mem[0] = 0x22; // LD (B229), HL
	cpu->mem[1] = 0x29;
	cpu->mem[2] = 0xB2;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0xB229] == 0x3A);
	CU_ASSERT(cpu->mem[0xB22A] == 0x48);
	
}

void ld_nn_ind_dd_test(void) {
	cpu_reset();
	
	BC = 0x4644;
	cpu->mem[0] = 0xED;
	cpu->mem[1] = 0x43; // LD (nn), BC
	cpu->mem[2] = 0x00;
	cpu->mem[3] = 0x10;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x1000] == 0x44);
	CU_ASSERT(cpu->mem[0x1001] == 0x46);
}

void ld_nn_ind_IX_IY_test(void) {
	cpu_reset();
	
	IX = 0x5A30;
	IY = 0x4174;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x22; // LD (4392h), IX
	cpu->mem[2] = 0x92;
	cpu->mem[3] = 0x43;
	
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0x22; // LD (4392h), IX
	cpu->mem[6] = 0x38;
	cpu->mem[7] = 0x88;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x4392] == 0x30);
	CU_ASSERT(cpu->mem[0x4393] == 0x5A);
	
	CU_ASSERT(cpu->mem[0x8838] == 0x74);
	CU_ASSERT(cpu->mem[0x8839] == 0x41);
	
}

void ld_sp_hl_IX_IY_test(void) {
	cpu_reset();
	
	HL = 0x442E;
	IX = 0x98DA;
	IY = 0xA227;
	
	cpu->mem[0] = 0xF9;
	cpu->mem[1] = 0xDD;
	cpu->mem[2] = 0xF9;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0xF9;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(SP == 0x442E);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(SP == 0x98DA);
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(SP == 0xA227);
}

void push_test(void) {
	cpu_reset();
	
	AF = 0x2233;
	IX = 0xAABB;
	IY = 0xCCDD;
	SP = 0x1007;
	
	cpu->mem[0] = 0xF5; // PUSH AF
	cpu->mem[1] = 0xDD;
	cpu->mem[2] = 0xE5; // PUSH IX
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0xE5; // PUSH IY
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x1006] == 0x22);
	CU_ASSERT(cpu->mem[0x1005] == 0x33);
	
	CU_ASSERT(cpu->mem[0x1004] == 0xAA);
	CU_ASSERT(cpu->mem[0x1003] == 0xBB);
	
	CU_ASSERT(cpu->mem[0x1002] == 0xCC);
	CU_ASSERT(cpu->mem[0x1001] == 0xDD);
	CU_ASSERT(SP == 0x1001);
}

void pop_test(void) {
	cpu_reset();
	
	SP = 0x1000;
	cpu->mem[0x1000] = 0x55;
	cpu->mem[0x1001] = 0x33;
	cpu->mem[0x1002] = 0xFF;
	cpu->mem[0x1003] = 0x45;
	cpu->mem[0x1004] = 0x66;
	cpu->mem[0x1005] = 0x77;
	
	cpu->mem[0] = 0xE1;	// POP HL
	cpu->mem[1] = 0xDD;
	cpu->mem[2] = 0xE1; // POP IX
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0xE1; // POP IY
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(HL == 0x3355);
	CU_ASSERT(IX == 0x45FF);
	CU_ASSERT(IY == 0x7766);
	CU_ASSERT(SP == 0x1006);
}
