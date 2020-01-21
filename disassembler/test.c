#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xDC;	// CALL C, 45ACh	// 11 011 100
	mem[1] = 0xAC;
	mem[2] = 0x45;

	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	return 0;
}
