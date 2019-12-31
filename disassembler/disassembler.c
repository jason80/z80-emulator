#include "disassembler.h"

#include <string.h>
#include <stdio.h>

typedef union {
	uint8_t byte;
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t z : 3;
		uint8_t y : 3;
		uint8_t x : 2;
		#else
		uint8_t x : 2;
		uint8_t y : 3;
		uint8_t z : 3;
		#endif
	};
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t _z : 3;
		uint8_t q : 1;
		uint8_t p : 2;
		uint8_t _x : 2;
		#else
		uint8_t _x : 2;
		uint8_t p : 2;
		uint8_t q : 1;
		uint8_t _z : 3;
		#endif
	};
} opcode_t;

// For relative jumps, gets the absolute from a relative value
uint16_t get_absolute_address(uint8_t relative, uint16_t address);

uint16_t dis_x0(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code);
uint16_t dis_x1(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code);
uint16_t dis_x2(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code);
uint16_t dis_x3(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code);

uint16_t disassemble(uint8_t mem[], uint16_t address, char* code) {
	opcode_t opcode;
	uint8_t prefix;
	uint8_t byte;
	
	byte = mem[address]; address ++;
	
	// Detect prefix
	if (0xDD == byte || 0xFD == byte) {
		prefix = byte;
		byte = mem[address]; address ++;
	}
	
	opcode.byte = byte;
	
	if (0xED == byte) {
		
	} else if (0xCB == byte) {
		
	} else {
		switch (opcode.x) {
		case 0:	// x = 0
			return dis_x0(opcode, mem, &address, code);
		case 1: // x = 1
			return dis_x1(opcode, mem, &address, code);
		case 2: // x = 2
			return dis_x2(opcode, mem, &address, code);
		case 3: // x = 3
			return dis_x3(opcode, mem, &address, code);
		}
	}
}

uint16_t dis_x0(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code)  {
	
	uint8_t byte;
	
	switch (opcode.z) {
	case 0: // z = 0
		switch (opcode.y) {
		case 0: // y = 0
			strcpy(code, "NOP");
			break;
		case 1: // y = 1
			strcpy(code, "EX AF, AF'");
			break;
		case 2: // y = 2
			byte = mem[*address]; (*address) ++;
			sprintf(code, "DJNZ %.4Xh", get_absolute_address(byte, *address));
			//djnz();				// DJNZ e
			break;
		case 3: // y = 3
			//jump_relative();	// JR e
			break;
		case 4: // y = 4
			//jr_nz_rel();		// JR NZ, e
			break;
		case 5: // y = 5
			//jr_z_rel();			// JR Z, e
			break;
		case 6: // y = 6
			//jr_nc_rel();		// JR NC, e
			break;
		case 7: // y = 7
			//jr_c_rel();			// JR C, e
			break;
		}
		break;
	}
	
	return *address;
}

uint16_t dis_x1(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code) {
	return *address;
}

uint16_t dis_x2(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code) {
	return *address;
}

uint16_t dis_x3(opcode_t opcode, uint8_t mem[], uint16_t* address, char* code) {
	return *address;
}

uint16_t get_absolute_address(uint8_t relative, uint16_t address) {
	relative += 2;
	
	union {
		uint8_t uns;
		int8_t sig;
	} value;
	
	value.uns = relative;
	
	return address + value.sig;
}
