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
	FLAG_Z = (*reg8 & 0x80) ? 1 : 0;
	
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
