#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0x13;	// INC DE	// 00 010 011
	mem[1] = 0xDD;
	mem[2] = 0x23;	// INC IX	// 00 100 011
	mem[3] = 0xFD;
	mem[4] = 0x23;	// INC IY	// 00 100 011

	mem[5] = 0x1B;	// DEC DE	// 00 011 011
	mem[6] = 0xDD;
	mem[7] = 0x2B;	// DEC IX	// 00 101 011
	mem[8] = 0xFD;
	mem[9] = 0x2B;	// DEC IY	// 00 101 011
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 1, code);
	printf("%s\n", code);

	disassemble(mem, 3, code);
	printf("%s\n", code);

	disassemble(mem, 5, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	disassemble(mem, 8, code);
	printf("%s\n", code);

	return 0;
}
