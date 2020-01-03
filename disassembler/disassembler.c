#include "disassembler.h"

#include <string.h>
#include <stdio.h>

#include "dis_tables.h"

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

uint16_t dis_x0(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code);
uint16_t dis_x1(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code);
uint16_t dis_x2(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code);
uint16_t dis_x3(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code);

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
			return dis_x0(opcode, prefix, mem, &address, code);
		case 1: // x = 1
			return dis_x1(opcode, prefix, mem, &address, code);
		case 2: // x = 2
			return dis_x2(opcode, prefix, mem, &address, code);
		case 3: // x = 3
			return dis_x3(opcode, prefix, mem, &address, code);
		}
	}
	
	return address;
}

uint16_t dis_x0(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code)  {
	
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
			break;
		case 3: // y = 3
			byte = mem[*address]; (*address) ++;
			sprintf(code, "JR %.4Xh", get_absolute_address(byte, *address));
			break;
		case 4: // y = 4
			byte = mem[*address]; (*address) ++;
			sprintf(code, "JR NZ, %.4Xh", get_absolute_address(byte, *address));
			break;
		case 5: // y = 5
			byte = mem[*address]; (*address) ++;
			sprintf(code, "JR Z, %.4Xh", get_absolute_address(byte, *address));
			break;
		case 6: // y = 6
			byte = mem[*address]; (*address) ++;
			sprintf(code, "JR NC, %.4Xh", get_absolute_address(byte, *address));
			break;
		case 7: // y = 7
			byte = mem[*address]; (*address) ++;
			sprintf(code, "JR C, %.4Xh", get_absolute_address(byte, *address));
			break;
		}
		break;
	case 1: { // z = 1
		char reg[3];
		switch (opcode.q) {
			case 0: {	// q = 0
				
				uint8_t n0, n1;	// Fetch 16 word
				n0 = mem[*address]; (*address) ++;
				n1 = mem[*address]; (*address) ++;
				
				if (prefix == 0xDD)
					sprintf(code, "LD IX, %.2X%.2Xh", n1, n0);
				else if (prefix == 0xFD)
					sprintf(code, "LD IY, %.2X%.2Xh", n1, n0);
				else {
					table_rp(opcode.p, reg);
					sprintf(code, "LD %s, %.2X%.2Xh", reg,  n1, n0);
				} }
				break;
			case 1:
				if (prefix == 0xDD) {
					table_rp_IX(opcode.p, reg);
					sprintf(code, "ADD IX, %s", reg);
				} else if (prefix == 0xFD) {
					table_rp_IY(opcode.p, reg);
					sprintf(code, "ADD IY, %s", reg);
				} else {
					table_rp(opcode.p, reg);
					sprintf(code, "ADD HL, %s", reg);
				}
				break;
		} }
		break;

	case 2: // z = 2 
		switch (opcode.q) {
			case 0: // q = 0
				switch (opcode.p) {
				case 0: // p = 0
					strcpy(code, "LD (BC), A");
					break;
				case 1: // p = 1
					strcpy(code, "LD (DE), A");
					break;
				case 2: { // p = 2
					uint8_t n0, n1;	// Fetch 16 word
					n0 = mem[*address]; (*address) ++;
					n1 = mem[*address]; (*address) ++;

					if (prefix == 0xDD)
						sprintf(code, "LD (%.2X%.2Xh), IX", n1, n0);
					else if (prefix == 0xFD)
						sprintf(code, "LD (%.2X%.2Xh), IY", n1, n0);
					else
						sprintf(code, "LD (%.2X%.2Xh), HL", n1, n0);
					}
					break;
				case 3: { // p = 3
					uint8_t n0, n1;	// Fetch 16 word
					n0 = mem[*address]; (*address) ++;
					n1 = mem[*address]; (*address) ++;
					sprintf(code, "LD (%.2X%.2Xh), A", n1, n0);
					}
					break;
				}
				break;
			case 1: // q = 1
				switch (opcode.p) {
				case 0: // p = 0
					strcpy(code, "LD A, (BC)");
					break;
				case 1: // p = 1
					strcpy(code, "LD A, (DE)");
					break;
				case 2: { // p = 2
					uint8_t n0, n1;	// Fetch 16 word
					n0 = mem[*address]; (*address) ++;
					n1 = mem[*address]; (*address) ++;
					if (prefix == 0xDD)
						sprintf(code, "LD IX, (%.2X%.2Xh)", n1, n0);
					else if (prefix == 0xFD)
						sprintf(code, "LD IY, (%.2X%.2Xh)", n1, n0);
					else
						sprintf(code, "LD HL, (%.2X%.2Xh)", n1, n0);
					}
					break;
				case 3: { // p = 3
					uint8_t n0, n1;	// Fetch 16 word
					n0 = mem[*address]; (*address) ++;
					n1 = mem[*address]; (*address) ++;
					sprintf(code, "LD A, (%.2X%.2Xh)", n1, n0);
					}
					break;
				}
				break;
		}
		break;

	case 3: { // z = 3
		char reg[3];

		if (opcode.q == 0) {	// q = 0
			if (prefix == 0) {
				table_rp(opcode.p, reg);
				sprintf(code, "INC %s", reg);
			} else if (prefix == 0xDD)
				strcpy(code, "INC IX");
			else if (prefix == 0xFD)
				strcpy(code, "INC IY");
		} else {
			if (prefix == 0) { // q = 1
				table_rp(opcode.p, reg);
				sprintf(code, "DEC %s", reg);
			} else if (prefix == 0xDD)
				strcpy(code, "DEC IX");
			else if (prefix == 0xFD)
				strcpy(code, "DEC IY");
		}
		}
		break;
		
	}
	
	return *address;
}

uint16_t dis_x1(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code) {
	return *address;
}

uint16_t dis_x2(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code) {
	return *address;
}

uint16_t dis_x3(opcode_t opcode, uint8_t prefix, uint8_t mem[], uint16_t* address, char* code) {
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
