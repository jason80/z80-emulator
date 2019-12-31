#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[20];
	char code[30];
	
	mem[0] = 0x00;		// NOP			// 00 000 000
	mem[1] = 0x08;		// EX AF, AF'	// 00 001 000
	mem[2] = 0x10;		// DJNZ 05h		// 00 010 000
	mem[3] = 0x03;		// 05h
	
	disassemble(mem, 0, code);
	printf("%s\n", code);
	
	disassemble(mem, 1, code);
	printf("%s\n", code);
	
	disassemble(mem, 2, code);
	printf("%s\n", code);
	
	return 0;
}
