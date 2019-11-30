#ifndef __ROT_SHIFT_H
#define __ROT_SHIFT_H

int init_rot_shift_suite(void);
int clean_rot_shift_suite(void);

// Rotate tests
void rlca_test(void);
void rla_test(void);
void rrca_test(void);
void rra_test(void);

void rlc_r_test(void);
void rlc_hl_test(void);
void rlc_IX_IY_test(void);

void rl_r_test(void);
void rl_IX_IY_test(void);

void rrc_r_test(void);
void rrc_hl_test(void);

void rr_IX_IY_test(void);

// Shift tests
void sla_r_test(void);

void sra_IX_test(void);

void srl_hl_test(void);

// BCD rotate tests
void rld_test(void);
void rrd_test(void);

#endif
