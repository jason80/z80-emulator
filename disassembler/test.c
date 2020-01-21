#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xEE;	// XOR 45h	// 11 101 110
	mem[1] = 0x45;

	mem[2] = 0xFE;	// CP 10h	// 11 111 110
	mem[3] = 0x10;

	mem[4] = 0xE6;	// ADD ABh	// 11 100 110
	mem[5] = 0xAB;



	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 4, code);
	printf("%s\n", code);


	return 0;
}
