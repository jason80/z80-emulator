#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xAB;	// XOR E				// 10 101 011

	mem[1] = 0xDD;
	mem[2] = 0x8E;	// ADC A, (IX + AAh)	// 10 001 110
	mem[3] = 0xAA;

	mem[4] = 0xFD;
	mem[5] = 0x9E;	// SBC A, (IY + 33h)	// 10 011 110
	mem[6] = 0x33;
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 1, code);
	printf("%s\n", code);

	disassemble(mem, 4, code);
	printf("%s\n", code);

	return 0;
}
