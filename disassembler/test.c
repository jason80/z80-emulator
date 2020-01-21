#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xDC;	// CALL C, 45ACh	// 11 011 100
	mem[1] = 0xAC;
	mem[2] = 0x45;

	mem[3] = 0xDD;
	mem[4] = 0xC5;	// PUSH IX		// 11 000 101

	mem[5] = 0xFD;
	mem[6] = 0xC5;	// PUSH IY		// 11 000 101

	mem[7] = 0xE5;	// PUSH HL		// 11 100 101

	mem[8] = 0xCD;	// CALL 0101h	// 11 001 101
	mem[9] = 0x01;
	mem[10] = 0x01;

	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 3, code);
	printf("%s\n", code);

	disassemble(mem, 5, code);
	printf("%s\n", code);

	disassemble(mem, 7, code);
	printf("%s\n", code);

	disassemble(mem, 8, code);
	printf("%s\n", code);

	return 0;
}
