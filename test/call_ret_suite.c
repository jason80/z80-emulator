#include "call_ret_suite.h"

#include <CUnit/CUnit.h>

#include "../core/cpu.h"
#include "../core/execute.h"

int init_call_ret_suite(void) {
	cpu_init();
	return 0;
}

int clean_call_ret_suite(void) {
	cpu_clean();
	return 0;
}

void call_nn_test(void) {
	
	cpu_reset();
	
	PC = 0x1A47;
	SP = 0x3002;
	
	cpu->mem[0x1A47] = 0xCD; // CALL 2135h
	cpu->mem[0x1A48] = 0x35;
	cpu->mem[0x1A49] = 0x21;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x3000] == 0x4A);
	CU_ASSERT(cpu->mem[0x3001] == 0x1A);
	CU_ASSERT(SP == 0x3000);
	CU_ASSERT(PC == 0x2135);
	
}

void call_cc_nn_test(void) {
	
	cpu_reset();
	
	FLAG_C = 0;

	PC = 0x1A47;
	SP = 0x3002;
	
	cpu->mem[0x1A47] = 0xD4; // CALL NC, 2135h
	cpu->mem[0x1A48] = 0x35;
	cpu->mem[0x1A49] = 0x21;
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(cpu->mem[0x3000] == 0x4A);
	CU_ASSERT(cpu->mem[0x3001] == 0x1A);
	CU_ASSERT(SP == 0x3000);
	CU_ASSERT(PC == 0x2135);
}

void ret_test(void) {
	cpu_reset();
	
	PC = 0x3535;
	SP = 0x2000;
	cpu->mem[0x2000] = 0xB5;
	cpu->mem[0x2001] = 0x18;
	
	cpu->mem[0x3535] = 0xC9; // RET
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(SP == 0x2002);
	CU_ASSERT(PC == 0x18B5);
}

void ret_cc_test(void) {
	cpu_reset();
	
	FLAG_S = 1;
	
	PC = 0x3535;
	SP = 0x2000;
	cpu->mem[0x2000] = 0xB5;
	cpu->mem[0x2001] = 0x18;
	
	cpu->mem[0x3535] = 0xF8; // RET M
	
	cpu_fetch();
	cpu_execute();
	
	CU_ASSERT(SP == 0x2002);
	CU_ASSERT(PC == 0x18B5);
}
