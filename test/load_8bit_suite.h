#ifndef __LOAD_8BIT_SUITE_H
#define __LOAD_8BIT_SUITE_H

int init_load_8bit_suite(void);
int clean_load_8bit_suite(void);

void ld_r_r_test(void);
void ld_r_n_test(void);

void ld_r_hl_test(void);
void ld_r_IX_IY_d_test(void);

void ld_hl_r_test(void);
void ld_IX_IY_d_r_test(void);

void ld_hl_n_test(void);
void ld_IX_IY_d_n_test(void);

void ld_a_bc_test(void);
void ld_a_de_test(void);
void ld_a_nn_test(void);

void ld_bc_a_test(void);
void ld_de_a_test(void);
void ld_nn_a_test(void);

void ld_a_i_r_test(void);
void ld_i_r_a_test(void);

#endif
