#ifndef __JUMP_SUITE_H
#define __JUMP_SUITE_H

int init_jump_suite(void);
int clean_jump_suite(void);

void jp_nn_test(void);
void jp_cc_nn_test(void);

void jr_e_test(void);
void jr_C_e_test(void);
void jr_NC_e_test(void);
void jr_Z_e_test(void);
void jr_NZ_e_test(void);

void jp_HL_test(void);
void jp_IX_IY_test(void);

#endif
