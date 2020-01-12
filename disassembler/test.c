#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xE1;	// POP HL		// 11 100 001

	mem[1] = 0xDD;
	mem[2] = 0xE1;	// POP IX		// 11 100 001

	mem[3] = 0xFD;
	mem[4] = 0xE1;	// POP IY		// 11 100 001

	mem[5] = 0xC9;	// RET 			// 11 001 001
	mem[6] = 0xD9;	// EXX 			// 11 011 001

	mem[7] = 0xE9;	// JP (HL)		// 11 101 001

	mem[8] = 0xDD;
	mem[9] = 0xE9;	// JP (IX)		// 11 101 001

	mem[10] = 0xFD;
	mem[11] = 0xE9;	// JP (IY)		// 11 101 001

	mem[12] = 0xF9;	// LD SP, HL	// 11 111 001

	mem[13] = 0xDD;
	mem[14] = 0xF9;	// LD SP, IX	// 11 111 001

	mem[15] = 0xFD;
	mem[16] = 0xF9;	// LD SP, IY	// 11 111 001
	
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

	disassemble(mem, 7, code);
	printf("%s\n", code);

	disassemble(mem, 8, code);
	printf("%s\n", code);

	disassemble(mem, 10, code);
	printf("%s\n", code);

	disassemble(mem, 12, code);
	printf("%s\n", code);

	disassemble(mem, 13, code);
	printf("%s\n", code);

	disassemble(mem, 15, code);
	printf("%s\n", code);
	return 0;
}
