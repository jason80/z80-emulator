#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0x3E;	// LD A, 32h	// 00 111 110
	mem[1] = 0x32;

	mem[2] = 0xDD;
	mem[3] = 0x3E;	// LD (IX + 3h), 88h	// 00 110 110
	mem[4] = 0x03;
	mem[5] = 0x88;

	mem[6] = 0xFD;
	mem[7] = 0x3E;	// LD (IY + 3h), 88h	// 00 110 110
	mem[8] = 0x03;
	mem[9] = 0x88;
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	return 0;
}
