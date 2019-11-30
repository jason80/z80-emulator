#include "rot_shift.h"

#include "cpu.h"
#include "alu.h"

void rotate_left(uint8_t* reg8);
void rotate_right(uint8_t* reg8);
void rotate_left_carry(uint8_t* reg8);
void rotate_right_carry(uint8_t* reg8);

void rotate_flag_check(uint8_t* reg8);

void rotate_left(uint8_t* reg8) {
	uint8_t carry;
	carry = (0x80 & *reg8) ? 1 : 0;
	*reg8 <<= 1;
	*reg8 |= FLAG_C;
	FLAG_C = carry;
	
	FLAG_H = 0;
	FLAG_N = 0;
}

void rotate_right(uint8_t* reg8) {
	uint8_t carry;
	carry = 0x01 & *reg8;
	*reg8 >>= 1;
	*reg8 |= FLAG_C ? 0x80 : 0x00;
	FLAG_C = carry;
	
	FLAG_H = 0;
	FLAG_N = 0;
}

void rotate_left_carry(uint8_t* reg8) {
	FLAG_C = (*reg8 & 0x80) ? 1 : 0;
	*reg8 <<= 1;
	*reg8 |= FLAG_C;
	
	FLAG_H = 0;
	FLAG_N = 0;
}

void rotate_right_carry(uint8_t* reg8) {
	FLAG_C = *reg8 & 1;
	*reg8 >>= 1;
	*reg8 |= FLAG_C ? 0x80 : 0x00;
	
	FLAG_H = 0;
	FLAG_N = 0;
}

void rotate_flag_check(uint8_t* reg8) {
	FLAG_S = (*reg8 & 0x80) ? 1 : 0;
	FLAG_Z = (*reg8 == 0) ? 1 : 0;
	
	// FLAG_PV (alu.h)
	parity_check(reg8);
	
	FLAG_H = 0;
	FLAG_N = 0;
}

void rlca(void) {
	rotate_left_carry(&A);
	cpu->ts = 4;
}

void rrca(void) {
	rotate_right_carry(&A);
	cpu->ts = 4;
}

void rla(void) {
	rotate_left(&A);
	cpu->ts = 4;
}

void rra(void) {
	rotate_right(&A);
	cpu->ts = 4;
}

void rlc(uint8_t* reg8) {
	rotate_left_carry(reg8);
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void rlc_relative(uint16_t reg16) {
	rlc(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void rl(uint8_t* reg8) {
	rotate_left(reg8);
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void rl_relative(uint16_t reg16) {
	rl(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void rrc(uint8_t* reg8) {
	rotate_right_carry(reg8);
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void rrc_relative(uint16_t reg16) {
	rrc(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void rr(uint8_t* reg8) {
	rotate_right(reg8);
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void rr_relative(uint16_t reg16) {
	rr(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void sla(uint8_t* reg8) {
	FLAG_C = (*reg8 & 0x80) ? 1 : 0;
	*reg8 <<= 1;
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void sla_relative(uint16_t reg16) {
	sla(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void sra(uint8_t* reg8) {
	uint8_t tmp = *reg8 & 0x80;
	FLAG_C = (*reg8 & 1) ? 1 : 0;
	*reg8 >>= 1;
	*reg8 |= tmp;
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void sra_relative(uint16_t reg16) {
	sra(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void srl(uint8_t* reg8) {
	FLAG_C = (*reg8 & 1) ? 1 : 0;
	*reg8 >>= 1;
	rotate_flag_check(reg8);
	cpu->ts = 8;
}

void srl_relative(uint16_t reg16) {
	srl(&cpu->mem[reg16 + BRL]);
	cpu->ts = 23;
}

void rld(void) {
	uint8_t new_a;
	uint8_t hl = cpu->mem[HL];
	
	new_a = hl >> 4;
	hl <<= 4;
	hl |= A & 0x0F;
	
	A &= 0xF0;
	A |= new_a;
	cpu->mem[HL] = hl;
	
	rotate_flag_check(&A);
	cpu->ts = 18;
}

