#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[20];
	char code[30];
	
	mem[0] = 0x00;		// NOP			// 00 000 000
	mem[1] = 0x08;		// EX AF, AF'	// 00 001 000
	mem[2] = 0x10;		// DJNZ 05h		// 00 010 000
	mem[3] = 0x03;		// 05h
	mem[4] = 0x18;		// JR 23h		// 00 011 000
	mem[5] = 0x23;		// 23h
	mem[6] = 0x20;		// JR NZ, 15h 	// 00 100 000
	mem[7] = 0x15;		// 15h
	mem[8] = 0x38;		// JR C, ABh	// 00 111 000
	mem[9] = 0xAB;		// ABh
	
	disassemble(mem, 0, code);
	printf("%s\n", code);
	
	disassemble(mem, 1, code);
	printf("%s\n", code);
	
	disassemble(mem, 2, code);
	printf("%s\n", code);
	
	disassemble(mem, 4, code);
	printf("%s\n", code);
	
	disassemble(mem, 6, code);
	printf("%s\n", code);
	
	disassemble(mem, 8, code);
	printf("%s\n", code);
	
	return 0;
}
