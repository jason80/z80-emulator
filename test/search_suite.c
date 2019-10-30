#include "search_suite.h"

#include "../core/cpu.h"

int init_search_suite(void) {
	cpu_init();
	return 0;
}

int clean_search_suite(void) {
	cpu_clean();
	return 0;
}


