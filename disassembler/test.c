#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xC3;	// JP FFEEh		// 11 000 011
	mem[1] = 0xEE;
	mem[2] = 0xFF;

	mem[3] = 0xE3;	// EX (SP), HL	// 11 100 011

	mem[4] = 0xDD;
	mem[5] = 0xE3;	// EX (SP), IX	// 11 100 011

	mem[6] = 0xFD;
	mem[7] = 0xE3;	// EX (SP), IY	// 11 100 011

	mem[8] = 0xEB;	// EX DE, HL	// 11 101 011
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 3, code);
	printf("%s\n", code);

	disassemble(mem, 4, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	disassemble(mem, 8, code);
	printf("%s\n", code);

	return 0;
}
