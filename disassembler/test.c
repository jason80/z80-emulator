#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0x02;	// LD (BC), A	// 00 000 010
	mem[1] = 0x12;	// LD (DE), A	// 00 010 010

	mem[2] = 0x22;	// LD (nn), HL	// 00 100 010
	mem[3] = 0x34;
	mem[4] = 0x12;

	mem[5] = 0xDD;
	mem[6] = 0x22;	// LD (nn), IX	// 00 100 010
	mem[7] = 0x11;
	mem[8] = 0x22;

	mem[9] = 0xFD;
	mem[10] = 0x22;	// LD (nn), IY	// 00 100 010
	mem[11] = 0xAA;
	mem[12] = 0xBB;

	mem[14] = 0x32;	// LD (nn), A	// 00 110 010
	mem[15] = 0xCD;
	mem[16] = 0xAB;

	mem[17] = 0x0A;	// LD A, (BC)	// 00 001 010
	mem[18] = 0x1A;	// LD A, (DE)	// 00 011 010

	mem[19] = 0xDD;
	mem[20] = 0x2A;	// LD IX, (nn)	// 00 101 010
	mem[21] = 0x76;
	mem[22] = 0x98;

	mem[23] = 0xFD;
	mem[24] = 0x2A;	// LD IY, (nn)	// 00 101 010
	mem[25] = 0x11;
	mem[26] = 0x11;

	mem[27] = 0x2A;	// LD HL, (nn)	// 00 101 010
	mem[28] = 0x55;
	mem[29] = 0x55;

	mem[30] = 0x3A;	// LD A, (nn)	// 00 111 010
	mem[31] = 0xDD;
	mem[32] = 0xCC;
	
	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 1, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 5, code);
	printf("%s\n", code);

	disassemble(mem, 9, code);
	printf("%s\n", code);

	disassemble(mem, 14, code);
	printf("%s\n", code);

	disassemble(mem, 17, code);
	printf("%s\n", code);

	disassemble(mem, 18, code);
	printf("%s\n", code);

	disassemble(mem, 19, code);
	printf("%s\n", code);
	
	disassemble(mem, 23, code);
	printf("%s\n", code);

	disassemble(mem, 27, code);
	printf("%s\n", code);

	disassemble(mem, 30, code);
	printf("%s\n", code);

	return 0;
}
