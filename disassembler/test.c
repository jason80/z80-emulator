#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xCB;
	mem[1] = 0x03; // RLC E // 00 000 011

	mem[2] = 0xDD;
	mem[3] = 0xCB;
	mem[4] = 0x45;
	mem[5] = 0x06; // RLC (IX + 45h) // 00 000 110

	mem[6] = 0xFD;
	mem[7] = 0xCB;
	mem[8] = 0x32;
	mem[9] = 0x06; // RLC (IY + 32h) // 00 000 110

	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	return 0;
}
