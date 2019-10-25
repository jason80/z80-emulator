#ifndef __LOAD_H
#define __LOAD_H

#include <inttypes.h>

// 8 bit load
void ld_8bit_8bit(uint8_t* reg1, uint8_t* reg2);
void ld_8bit_n(uint8_t* reg8);
void ld_8bit_indirect(uint8_t* reg8, uint16_t adr);
void ld_8bit_indirect_relative(uint8_t* reg8, uint16_t adr);
void ld_indirect_relative_8bit(uint16_t adr, uint8_t* reg8);
void ld_indirect_relative_n(uint16_t adr);


void ld_indirect_8bit(uint16_t adr, uint8_t* reg8);


void ld_indirect_nn_8bit(uint8_t* reg8);

void ld_8bit_indirect_nn(uint8_t* reg8);


void ld_16bit_nn(uint16_t* reg16);
void ld_indirect_nn_16bit(uint16_t* reg16);
void ld_16bit_indirect_nn(uint16_t* reg16);

void ld_sp_hl(void);
void ld_sp_ix(void);
void ld_sp_iy(void);

void push(uint16_t* reg16);
void pop(uint16_t* reg16);

#endif
