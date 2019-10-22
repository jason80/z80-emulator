#include "load_8bit_suite.h"

#include "CUnit/CUnit.h"

#include "../core/cpu.h"
#include "../core/execute.h"

int init_load_8bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_load_8bit_suite(void) {
	cpu_clean();
	return 0;
}

void ld_r_r_test(void) {
	cpu_reset();
	
	H = 0x8A;
	E = 0x10;
	
	cpu->mem[0] = 0x63; // LD H, E
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(H == 0x10);
	CU_ASSERT(E == 0x10);
}

void ld_r_n_test(void) {
	cpu_reset();
	
	cpu->mem[0] = 0x1E;	// LD E, 45h
	cpu->mem[1] = 0x45;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(E == 0x45);
}

void ld_r_hl_test(void) {
	cpu_reset();
	
	HL = 0x75A1;
	
	cpu->mem[0x75A1] = 0x58;
	
	cpu->mem[0] = 0x4E;	// LD C, (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(C == 0x58);
}

void ld_r_IX_IY_d_test(void) {
	cpu_reset();
	
	IX = 0x25AF;
	cpu->mem[0x25C8] = 0x39;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x46; // LD B, (IX + 19h)
	cpu->mem[2] = 0x19;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(B == 0x39);
	
	cpu_reset();
	
	IY = 0x25AF;
	cpu->mem[0x25C8] = 0x39;
	
	cpu->mem[0] = 0xFD;
	cpu->mem[1] = 0x46; // LD B, (IY + 19h)
	cpu->mem[2] = 0x19;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(B == 0x39);
	
}

void ld_hl_r_test(void) {
	cpu_reset();
	B = 0x29;
	HL = 0x2146;
	cpu->mem[0] = 0x70; // LD (HL), B
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x2146] == 0x29);	
}

void ld_IX_IY_d_r_test(void) {
	cpu_reset();
	C = 0x1C;
	IX = 0x3100;
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x71;	// LD (IX + 06h), C
	cpu->mem[2] = 0x06;
	
	cpu_fetch();
	cpu_execute();
	
	C = 0x48;
	IY = 0x2A11;
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0x71;	// LD (IY + 06h), C
	cpu->mem[5] = 0x04;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x3106] == 0x1C);
	CU_ASSERT(cpu->mem[0x2A15] == 0x48);
}

void ld_hl_n_test(void) {
	cpu_reset();
	HL = 0x4444;
	cpu->mem[0] = 0x36;	// LD (HL), 0x28
	cpu->mem[1] = 0x28;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x4444] == 0x28);
}

void ld_IX_IY_d_n_test(void) {
	cpu_reset();
	IX = 0x219A;
	IY = 0xA940;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0x36; // LD (IX + 5h), 5Ah
	cpu->mem[2] = 0x05;
	cpu->mem[3] = 0x5A;
	
	cpu->mem[4] = 0xFD;
	cpu->mem[5] = 0x36; // LD (IY + 10h), 97h
	cpu->mem[6] = 0x10;
	cpu->mem[7] = 0x97;
	
	cpu_fetch();
	cpu_execute();
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x219F] == 0x5A);
	CU_ASSERT(cpu->mem[0xA950] == 0x97);
	
}

void ld_a_bc_test(void) {
	cpu_reset();
	BC = 0x4747;
	cpu->mem[0x4747] = 0x12;
	
	cpu->mem[0] = 0x0A;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x12);
}

void ld_a_de_test(void) {
	cpu_reset();
	DE = 0x30A2;
	cpu->mem[0x30A2] = 0x22;
	
	cpu->mem[0] = 0x1A;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x22);
}

void ld_a_nn_test(void) {
	cpu_reset();
	
	cpu->mem[0x8832] = 0x04;
	
	cpu->mem[0] = 0x3A;
	cpu->mem[1] = 0x32;
	cpu->mem[2] = 0x88;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(A == 0x04);
}

void ld_bc_a_test(void) {
	cpu_reset();
	
	A = 0x7A;
	BC = 0x1212;
	
	cpu->mem[0] = 0x02;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x1212] == 0x7A);

}
