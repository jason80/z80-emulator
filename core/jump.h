#ifndef __JUMP_H
#define __JUMP_H

#include <inttypes.h>

void jump(void);
void jump_conditional(int);

void jump_relative(void);

void jr_c_rel(void);
void jr_nc_rel(void);
void jr_z_rel(void);
void jr_nz_rel(void);

void jump_reg(uint16_t*);

#endif

