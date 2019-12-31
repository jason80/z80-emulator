#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[20];
	char code[30];
	
	mem[0] = 0xDD;		// PREFIX
	mem[1] = 0x01;		// LD IX, 34ABh	// 00 000 001
	mem[2] = 0xAB;		// ABh
	mem[3] = 0x34;		// 34h
	mem[4] = 0xFD;		// PREFIX
	mem[5] = 0x01;		// LD IY, 1212h	// 00 000 001
	mem[6] = 0x12;		// 12
	mem[7] = 0x12;		// 12
	mem[8] = 0x31;		// LD SP, 2020h	// 00 110 001
	mem[9] = 0x20;
	mem[10] = 0x20;
	
	mem[11] = 0xDD;
	mem[12] = 0x29;		// ADD IX, IX	// 00 101 001
	mem[13] = 0xFD;
	mem[14] = 0x29;		// ADD IY, IY	// 00 101 001
	mem[15] = 0x29;		// ADD HL, HL	// 00 101 001
	
	disassemble(mem, 0, code);
	printf("%s\n", code);
	
	disassemble(mem, 4, code);
	printf("%s\n", code);
	
	disassemble(mem, 8, code);
	printf("%s\n", code);
	
	disassemble(mem, 11, code);
	printf("%s\n", code);
	
	disassemble(mem, 13, code);
	printf("%s\n", code);
	
	disassemble(mem, 15, code);
	printf("%s\n", code);
	
	return 0;
}
