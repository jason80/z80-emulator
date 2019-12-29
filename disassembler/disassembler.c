#include "disassembler.h"

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

uint16_t disassemble(uint8_t mem[], uint16_t address, char* code) {
	opcode_t opcode;
	uint8_t prefix;
	uint8_t byte;
	
	byte = mem[address]; address ++;
	
	// Detect prefix
	if (0xDD == byte || 0xFD == byte) {
		cpu->prefix = byte;
		byte = mem[address]; address ++;
	}
	
	opcode.byte = byte;
	
	if (0xED == byte) {
		
	} else if (0xCB == byte) {
		
	} else {
		
	}
}
