#include "cp_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_cp_suite(void) {
	cpu_init();
	return 0;
}

int clean_cp_suite(void) {
	cpu_clean();
	return 0;
}

void cp_A_r_test(void) {
	cpu_reset();
	A = 32;
	H = 32;
	
	cpu->mem[0] = 0xBC; // CP H
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 1); // A == H
	CU_ASSERT(FLAG_PV == 0);
	CU_ASSERT(FLAG_C == 0);
}

void cp_A_n_test(void) {
	cpu_reset();
	A = 120;
	
	cpu->mem[0] = 0xFE;	// CP 100
	cpu->mem[1] = 100;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0); // A != 100
	CU_ASSERT(FLAG_PV == 0); 
	CU_ASSERT(FLAG_C == 0);	// A > 100
}

void cp_A_HL_ref_test(void) {
	cpu_reset();
	A = 45;
	HL = 0xABC0;
	cpu->mem[0xABC0] = 96;
	
	cpu->mem[0] = 0xBE; // CP (HL)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0); // A != (HL)
	CU_ASSERT(FLAG_PV == 0); 
	CU_ASSERT(FLAG_C == 1);	// A < (HL)
}

void cp_A_IX_IY_relative_test(void) {
	cpu_reset();
	
	A = -80;
	IX = 0x0030;
	IY = 0x1030;
	cpu->mem[0x0034] = 123;
	cpu->mem[0x1034] = -100;
	
	cpu->mem[0] = 0xDD;
	cpu->mem[1] = 0xBE;	// CP (IX + 4)
	cpu->mem[2] = 4;
	
	cpu->mem[3] = 0xFD;
	cpu->mem[4] = 0xBE;	// CP (IY + 4)
	cpu->mem[5] = 4;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0); // A != (IX + 4)
	CU_ASSERT(FLAG_PV != FLAG_S); // A < (IX + 4)
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(FLAG_Z == 0); // A != (IX + 4)
	CU_ASSERT(FLAG_PV == FLAG_S); // A >= (IX + 4)

}
