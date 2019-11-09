#ifndef __CPU_H
#define __CPU_H

#include <inttypes.h>

// 16 BIT WORD REGISTER
typedef union {
	uint16_t word;
	
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t l, h;
		#else
		uint8_t h, l;
		#endif
	};
	
} word_t;

// SPECIAL FLAG 16 BIT WORD REGISTER
typedef union {
	uint16_t word;
	
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t l, h;
		#else
		uint8_t h, l;
		#endif
	};
	
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint8_t f_c : 1;
		uint8_t f_n : 1;
		uint8_t f_pv : 1;
		uint8_t _f_x1 : 1;
		uint8_t f_h : 1;
		uint8_t _f_x2 : 1;
		uint8_t f_z : 1;
		uint8_t f_s : 1;
		uint8_t _rest : 8;
		#else
		uint8_t _rest : 8;
		uint8_t f_s : 1;
		uint8_t f_z : 1;
		uint8_t _f_x2 : 1;
		uint8_t f_h : 1;
		uint8_t _f_x1 : 1;
		uint8_t f_pv : 1;
		uint8_t f_n : 1;
		uint8_t f_c : 1;
		#endif
	};
} flag_word_t;

// GENERAL PURPOSE REGISTERS
typedef struct {
	flag_word_t af;
	word_t bc, de, hl;
} gpreg_t;

// CPU REGISTERS
typedef struct {
	
	gpreg_t regs; // MAIN REGISTERS
	gpreg_t alter; // ALTERNATE REGISTERS
	
	
	uint8_t i, r;
	uint16_t ix, iy, sp, pc;
	
	
	// Internal
	word_t br;		// Buffer Register
	uint8_t ir;		// Instruction Register
	int prefix, halt;
	
	uint8_t	fetch_status;
	
	uint8_t mem[0x10000];	// Memory
	word_t adr;				// Memory address
	
	// Timing
	uint8_t ts;
} cpu_t;

extern cpu_t* cpu;

// Main registers
#define A		cpu->regs.af.h
#define F		cpu->regs.af.l
#define B		cpu->regs.bc.h
#define C		cpu->regs.bc.l
#define D		cpu->regs.de.h
#define E		cpu->regs.de.l
#define H		cpu->regs.hl.h
#define L		cpu->regs.hl.l

#define AF		cpu->regs.af.word
#define BC		cpu->regs.bc.word
#define DE		cpu->regs.de.word
#define HL		cpu->regs.hl.word

// F Flags
#define FLAG_C	cpu->regs.af.f_c
#define FLAG_N	cpu->regs.af.f_n
#define FLAG_PV	cpu->regs.af.f_pv
#define FLAG_H	cpu->regs.af.f_h
#define FLAG_Z	cpu->regs.af.f_z
#define FLAG_S	cpu->regs.af.f_s

#define I		cpu->i
#define R		cpu->r
#define IX		cpu->ix
#define IY		cpu->iy
#define SP		cpu->sp
#define PC		cpu->pc

// Internal
#define BR		cpu->br.word
#define BRH		cpu->br.h
#define BRL		cpu->br.l
#define IR		cpu->ir

// Memory
#define ADR		cpu->adr.word
#define ADRH	cpu->adr.h
#define ADRL	cpu->adr.h
#define DATA	cpu->mem[cpu->adr.word]

// Fetch Status
#define FETCH_INST				0
#define FETCH_L					1
#define FETCH_H					2

void cpu_init(void);
void cpu_reset(void);

void cpu_clean(void);

void cpu_fetch(void);

#endif
