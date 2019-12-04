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

