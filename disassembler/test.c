#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xEA;	// JP PE, 30AAh		// 11 101 010
	mem[1] = 0xAA;
	mem[2] = 0x30;
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	return 0;
}
