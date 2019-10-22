#ifndef __EXECUTE_H
#define __EXECUTE_H

#include <inttypes.h>

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

void cpu_execute(void);

#endif
