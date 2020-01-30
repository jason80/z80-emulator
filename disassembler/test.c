#include <stdio.h>

#include "disassembler.h"

int main() {
	
	uint8_t mem[35];
	char code[35];
	
	mem[0] = 0xCB;
	mem[1] = 0x10; // RL B // 00 010 000

	mem[2] = 0xDD;
	mem[3] = 0xCB;
	mem[4] = 0xAA;
	mem[5] = 0x16; // RL (IX + AAh) // 00 010 110

	mem[6] = 0xFD;
	mem[7] = 0xCB;
	mem[8] = 0xBB;
	mem[9] = 0x16; // RL (IY + BBh) // 00 010 110

	mem[10] = 0xCB;
	mem[11] = 0x1F; // RR A // 00 011 111

	mem[12] = 0xDD;
	mem[13] = 0xCB;
	mem[14] = 0x10;
	mem[15] = 0x1E; // RR (IX + 10h) // 00 011 110

	mem[16] = 0xFD;
	mem[17] = 0xCB;
	mem[18] = 0xA1;
	mem[19] = 0x1E; // RR (IY + A1h) // 00 011 110

	disassemble(mem, 0, code);
	printf("%s\n", code);

	disassemble(mem, 2, code);
	printf("%s\n", code);

	disassemble(mem, 6, code);
	printf("%s\n", code);

	disassemble(mem, 10, code);
	printf("%s\n", code);

	disassemble(mem, 12, code);
	printf("%s\n", code);

	disassemble(mem, 16, code);
	printf("%s\n", code);

	return 0;
}
