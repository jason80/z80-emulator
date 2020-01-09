#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0x07;	// RLCA	// 00 000 111
	mem[1] = 0x0F;	// RRCA	// 00 001 111
	mem[2] = 0x17;	// RLA	// 00 010 111
	mem[3] = 0x1F;	// RRA	// 00 011 111
	mem[4] = 0x27;	// DAA	// 00 100 111
	mem[5] = 0x2F;	// CPL	// 00 101 111
	mem[6] = 0x37;	// SCF	// 00 110 111
	mem[7] = 0x3F;	// CCF	// 00 111 111
	
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 1, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 3, code);
	printf("%s\n", code);

	disassemble(mem, 4, code);
	printf("%s\n", code);

	disassemble(mem, 5, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	disassemble(mem, 7, code);
	printf("%s\n", code);

	return 0;
}
