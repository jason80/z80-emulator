#include <stdio.h>

#include <CUnit/Basic.h>

#include "cpu_suite.h"
#include "ld_suite.h"
#include "ex_suite.h"

int main(void) {
	
	CU_pSuite cpu_suite = NULL;
	CU_pSuite ld_suite = NULL;
	CU_pSuite ex_suite = NULL;
	
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	// CPU SUITE ---------------------------------------------------------
	cpu_suite = CU_add_suite("CPU", init_cpu_suite, clean_cpu_suite);
	if (NULL == cpu_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (	(NULL == CU_add_test(cpu_suite, "Endian", endian_test))			||
			(NULL == CU_add_test(cpu_suite, "Register", register_test))		||
			(NULL == CU_add_test(cpu_suite, "Fetch", fetch_test))
		
		) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// LD SUITE ----------------------------------------------------------
	ld_suite = CU_add_suite("LD", init_ld_suite, clean_ld_suite);
	if (NULL == ld_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (	(NULL == CU_add_test(ld_suite, "LD 8reg immediate", ld_8_immediate_test))	||
			(NULL == CU_add_test(ld_suite, "LD 16reg immediate", ld_16_immediate_test))	||
			(NULL == CU_add_test(ld_suite, "LD indirect reg", ld_indirect_reg_test))	||
			(NULL == CU_add_test(ld_suite, "LD reg indirect", ld_reg_indirect_test))	||
			(NULL == CU_add_test(ld_suite, "LD 8reg", ld_8_reg_test))					||
			(NULL == CU_add_test(ld_suite, "LD SP, HL", ld_sp_hl_test))					||
			(NULL == CU_add_test(ld_suite, "LD indirect nn", ld_indirect_nn_test))		||
			(NULL == CU_add_test(ld_suite, "LD 8bit indirect relative", ld_8_indirect_relative_test))		||
			(NULL == CU_add_test(ld_suite, "LD indirect relative 8 bit", ld_indirect_relative_8_test))		||
			(NULL == CU_add_test(ld_suite, "LD a i r", ld_a_i_r_test))					||
			(NULL == CU_add_test(ld_suite, "PUSH POP", push_pop_test))
		) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	ex_suite = CU_add_suite("EX", init_ex_suite, clean_ex_suite);
	if (NULL == ex_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (	(NULL == CU_add_test(ex_suite, "EX DE, HL", ex_de_hl_test))			||
			(NULL == CU_add_test(ex_suite, "EX AF, AF'", ex_af_af_test))		||
			(NULL == CU_add_test(ex_suite, "EXX", exx_test))					||
			(NULL == CU_add_test(ex_suite, "EX (SP), HL", ex_sp_hl_test))
		) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// RUN TESTS
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n");
	
	CU_cleanup_registry();
	
	return CU_get_error();
}
