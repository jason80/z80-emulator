#ifndef __ROT_SHIFT_H
#define __ROT_SHIFT_H

int init_rot_shift_suite(void);
int clean_rot_shift_suite(void);

void rlca_test(void);
void rla_test(void);
void rrca_test(void);
void rra_test(void);

void rlc_r_test(void);
void rlc_hl_test(void);
void rlc_IX_IY_test(void);

void rl_r_test(void);
void rl_IX_IY_test(void);

#endif
