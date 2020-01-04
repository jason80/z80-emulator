#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xDD;
	mem[1] = 0x34;	// INC (IX + 5h)	// 00 110 100
	mem[2] = 0x05;

	mem[3] = 0xFD;
	mem[4] = 0x34;	// INC (IY + 20h)	// 00 110 100
	mem[5] = 0x20;

	mem[5] = 0x3C;	// INC A			// 00 111 100
	mem[6] = 0x34;	// INC (HL)			// 00 110 100
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 3, code);
	printf("%s\n", code);

	disassemble(mem, 5, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	return 0;
}
