#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xDD;
	mem[1] = 0x35;	// DEC (IX + 5h)	// 00 110 101
	mem[2] = 0x05;

	mem[3] = 0xFD;
	mem[4] = 0x35;	// DEC (IY + 20h)	// 00 110 101
	mem[5] = 0x20;

	mem[5] = 0x3D;	// DEC A			// 00 111 101
	mem[6] = 0x35;	// DEC (HL)			// 00 110 101
	
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
