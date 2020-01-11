#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xE8;	// RET PE		// 11 101 000
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	return 0;
}
