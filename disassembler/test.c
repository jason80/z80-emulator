#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xCB;
	mem[1] = 0x08; // RRC B // 00 001 000

	mem[2] = 0xDD;
	mem[3] = 0xCB;
	mem[4] = 0xAA;
	mem[5] = 0x0E; // RLC (IX + AAh) // 00 001 110

	mem[6] = 0xFD;
	mem[7] = 0xCB;
	mem[8] = 0xBB;
	mem[9] = 0x0E; // RLC (IY + BBh) // 00 001 110

	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	return 0;
}
