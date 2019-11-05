#include "add_suite.h"

#include "../core/cpu.h"

int init_add_suite() {
	cpu_init();
	return 0;
}

int clean_add_suite() {
	cpu_clean();
	return 0;
}
