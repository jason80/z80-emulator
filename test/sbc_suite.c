#include "sbc_suite.h"

#include "../core/cpu.h"

int init_sbc_suite(void) {
	cpu_init();
	return 0;
}

int clean_sbc_suite(void) {
	cpu_clean();
	return 0;
}
