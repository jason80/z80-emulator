#ifndef __ALU_H
#define __ALU_H

#include <inttypes.h>

void alu(uint8_t operation, uint8_t* reg8);
void alu_n(uint8_t operation);
void alu_indirect(uint8_t operation, uint16_t* reg16);

void inc(uint8_t* reg8);
void inc_relative(uint16_t reg16);

void dec(uint8_t* reg8);
void dec_relative(uint16_t reg16);

void parity_check(uint8_t*);

#endif

