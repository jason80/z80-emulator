#include "adc_suite.h"

#include "../core/cpu.h"

int init_adc_suite(void) {
	cpu_init();
	return 0;
}

int clean_adc_suite(void) {
	cpu_clean();
	return 0;
}
