#ifndef __ROT_SHIFT_H
#define __ROT_SHIFT_H

#include <inttypes.h>

void rlca(void);
void rrca(void);
void rla(void);
void rra(void);

void rlc(uint8_t* reg8);
void rlc_relative(uint16_t reg16);

void rl(uint8_t* reg8);
void rl_relative(uint16_t reg16);

void rrc(uint8_t* reg8);
void rrc_relative(uint16_t reg16);

void rr(uint8_t* reg8);
void rr_relative(uint16_t reg16);

void sla(uint8_t* reg8);
void sla_relative(uint16_t reg16);

void sra(uint8_t* reg8);
void sra_relative(uint16_t reg16);

void srl(uint8_t* reg8);
void srl_relative(uint16_t reg16);

#endif
