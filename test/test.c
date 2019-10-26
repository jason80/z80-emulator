#include <stdio.h>

#include <CUnit/Basic.h>

#include "cpu_suite.h"
#include "load_8bit_suite.h"
#include "load_16bit_suite.h"
#include "exchange_suite.h"

int main(void) {
	
	CU_pSuite cpu_suite = NULL;
	CU_pSuite load_8bit_suite = NULL;
	CU_pSuite load_16bit_suite = NULL;
	CU_pSuite exchange_suite = NULL;
	
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
			(NULL == CU_add_test(cpu_suite, "Fetch", fetch_test))			||
			(NULL == CU_add_test(cpu_suite, "Flags", flags_test))
		
		) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// LOAD 8 BIT SUITE ----------------------------------------------------------
	load_8bit_suite = CU_add_suite("8 bit load", init_load_8bit_suite, clean_load_8bit_suite);
	if (NULL == load_8bit_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (	(NULL == CU_add_test(load_8bit_suite, "LD r, r'", ld_r_r_test))		||
			(NULL == CU_add_test(load_8bit_suite, "LD r, n", ld_r_n_test))		||
			(NULL == CU_add_test(load_8bit_suite, "LD r, (HL)", ld_r_hl_test))  ||
			(NULL == CU_add_test(load_8bit_suite, "LD r, (IX + d) / LD r, (IY + d)", ld_r_IX_IY_d_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD (HL), r", ld_hl_r_test))	||
			(NULL == CU_add_test(load_8bit_suite, "LD (IX + d), r / LD (IY + d), r", ld_IX_IY_d_r_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD (HL), n", ld_hl_n_test))	||
			(NULL == CU_add_test(load_8bit_suite, "LD (IX + d), n / LD (IY + d), n", ld_IX_IY_d_n_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD A, (BC)", ld_a_bc_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD A, (DE)", ld_a_de_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD A, (nn)", ld_a_nn_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD (BC), A", ld_bc_a_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD (DE), A", ld_de_a_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD (nn), A", ld_nn_a_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD A, I / LD A, R", ld_a_i_r_test)) ||
			(NULL == CU_add_test(load_8bit_suite, "LD I, A / LD R, A", ld_i_r_a_test))
			

		) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// LOAD 16 BIT SUITE
	load_16bit_suite = CU_add_suite("16 bit load", init_load_16bit_suite, clean_load_16bit_suite);
	if (NULL == load_16bit_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (	(NULL == CU_add_test(load_16bit_suite, "LD rr, nn", ld_rr_nn_test))					||
			(NULL == CU_add_test(load_16bit_suite, "LD IX, nn / LD IY, nn", ld_IX_IY_nn_test))	||
			(NULL == CU_add_test(load_16bit_suite, "LD HL, (nn)", ld_hl_nn_ind_test))			||
			(NULL == CU_add_test(load_16bit_suite, "LD dd, (nn)", ld_dd_nn_ind_test))			||
			(NULL == CU_add_test(load_16bit_suite, "LD IX, (nn) / LD IY, (nn)", ld_IX_IY_nn_ind_test)) ||
			(NULL == CU_add_test(load_16bit_suite, "LD (nn), HL", ld_nn_ind_hl_test))			||
			(NULL == CU_add_test(load_16bit_suite, "LD (nn), dd", ld_nn_ind_dd_test))			||
			(NULL == CU_add_test(load_16bit_suite, "LD (nn), IX / LD (nn), IY", ld_nn_ind_IX_IY_test)) ||
			(NULL == CU_add_test(load_16bit_suite, "LD SP, HL / LD SP, IX / LD SP, IY", ld_sp_hl_IX_IY_test)) ||
			(NULL == CU_add_test(load_16bit_suite, "PUSH", push_test)) 							||
			(NULL == CU_add_test(load_16bit_suite, "POP", pop_test))
		) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// EXCHANGE SUITE
	exchange_suite = CU_add_suite("Exchange", init_exchange_suite, clean_exchange_suite);
	if (NULL == exchange_suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (	(NULL == CU_add_test(exchange_suite, "EX DE, HL", ex_de_hl_test))	||
			(NULL == CU_add_test(exchange_suite, "EX AF, AF'", ex_af_af_test))
	) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	cpu_suite->fActive = CU_FALSE;
	load_8bit_suite->fActive = CU_FALSE;
	load_16bit_suite->fActive = CU_FALSE;
	//exchange_suite->fActive = CU_FALSE;
	
	// RUN TESTS
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n");
	
	CU_cleanup_registry();
	
	return CU_get_error();
}
