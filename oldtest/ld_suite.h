#ifndef __LD_SUITE_H
#define __LD_SUITE_H

int init_ld_suite(void);
int clean_ld_suite(void);

void ld_8_immediate_test(void);
void ld_16_immediate_test(void);

void ld_indirect_reg_test(void);
void ld_reg_indirect_test(void);

void ld_8_reg_test(void);

void ld_sp_hl_test(void);

void ld_indirect_nn_test(void);

void ld_8_indirect_relative_test(void);
void ld_indirect_relative_8_test(void);

void ld_a_i_r_test(void);

void push_pop_test(void);

#endif
