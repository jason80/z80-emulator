#include "sub_suite.h"

#include "../core/cpu.h"

int init_sub_suite(void) {
	cpu_init();
	return 0;
}

int clean_sub_suite(void) {
	cpu_clean();
	return 0;
}
