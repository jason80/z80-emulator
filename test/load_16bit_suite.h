#ifndef __LOAD_16BIT_SUITE_H
#define __LOAD_16BIT_SUITE_H

int init_load_16bit_suite(void);
int clean_load_16bit_suite(void);

void ld_rr_nn_test(void);
void ld_IX_IY_nn_test(void);

void ld_hl_nn_ind_test(void);
void ld_dd_nn_ind_test(void);
void ld_IX_IY_nn_ind_test(void);

void ld_nn_ind_hl_test(void);
void ld_nn_ind_dd_test(void);

#endif
