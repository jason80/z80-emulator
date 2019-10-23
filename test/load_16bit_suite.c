#include "load_16bit_suite.h"

#include "../core/cpu.h"

int init_load_16bit_suite(void) {
	cpu_init();
	return 0;
}

int clean_load_16bit_suite(void) {
	cpu_clean();
	return 0;
}

