#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0x76;	// HALT				// 01 110 110
	mem[1] = 0x5C;	// LD E, H			// 01 011 100

	mem[2] = 0xDD;
	mem[3] = 0x7E;	// LD A, (IX + 34h)	// 01 111 110
	mem[4] = 0x34;

	mem[5] = 0xDD;
	mem[6] = 0x70;	// LD (IX + 20h), B	// 01 110 000
	mem[7] = 0x20;

	mem[8] = 0xFD;
	mem[9] = 0x7E;	// LD A, (IY + 34h)	// 01 111 110
	mem[10] = 0x34;

	mem[11] = 0xFD;
	mem[12] = 0x70;	// LD (IY + 20h), B	// 01 110 000
	mem[13] = 0x20;
	
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 1, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 5, code);
	printf("%s\n", code);

	disassemble(mem, 8, code);
	printf("%s\n", code);

	disassemble(mem, 11, code);
	printf("%s\n", code);

	return 0;
}
