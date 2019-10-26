#include "exchange_suite.h"

#include "../core/cpu.h"

int init_exchange_suite(void) {
	cpu_init();
	return 0;
}

int clean_exchange_suite(void) {
	cpu_clean();
	return 0;
}
