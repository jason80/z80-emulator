#ifndef __ARITHM_16BIT_SUITE_H
#define __ARITHM_16BIT_SUITE_H

int init_arithm_16bit_suite(void);
int clean_arithm_16bit_suite(void);

void add16_hl_rr_test(void);
void adc16_hl_rr_test(void);
void sbc16_hl_rr_test(void);
void add16_IX_IY_rr_test(void);

void inc16_test(void);
void dec16_test(void);

#endif
