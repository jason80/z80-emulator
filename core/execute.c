#include "execute.h"

#include "cpu.h"
#include "tables.h"
#include "load.h"
#include "exchange.h"
#include "block_transfer.h"
#include "search.h"
#include "alu.h"

void execute_x0(opcode_t);
void execute_x1(opcode_t);
void execute_x2(opcode_t); // alu
void execute_x3(opcode_t);

void ed_prefixed(void);

void cpu_execute(void) {
	opcode_t opcode;
	
	if (0xDD == IR || 0xFD == IR) {
		cpu->prefix = IR;
		cpu->fetch_status = FETCH_INST;
		cpu_fetch();
	}
	
	opcode.byte = IR;
	
	if (0xED == IR) ed_prefixed();
	else {
	
		switch (opcode.x) {
		case 0:	// x = 0
			execute_x0(opcode);
			break;
		case 1: // x = 1
			execute_x1(opcode);
			break;
		case 2: // x = 2
			execute_x2(opcode);
			break;
		case 3: // x = 3
			execute_x3(opcode);
			break;
		}
	}
	
	cpu->prefix = 0;
	cpu->fetch_status = FETCH_INST;
}

void execute_x0(opcode_t opcode) {
	switch (opcode.z) {
	case 0: // z = 0
		switch (opcode.y) {
		case 0: // y = 0
			// NOP
			break;
		case 1: // y = 1
			ex_af_af();		// EX AF, AF'
			break;
		case 2: // y = 2
			break;
		case 3: // y = 3
			break;
		default: // y = 4 .. 7
			break;
		}
		break;
	case 1: // z = 1
		switch (opcode.q) {
			case 0:
				if (cpu->prefix == 0xDD)
					ld_16bit_nn(&IX);
				else if (cpu->prefix == 0xFD)
					ld_16bit_nn(&IY);
				else
					ld_16bit_nn(table_rp(opcode.p)); // LD rp[p], nn
				break;
			case 1:		// ADD HL, rp[p]
				break;
		}
		break;
	case 2: // z = 2 
		switch (opcode.q) {
			case 0: // q = 0
				switch (opcode.p) {
				case 0: // p = 0
					// LD (BC), A
					ld_indirect_8bit(BC, &A);
					break;
				case 1: // p = 1
					// LD (DE), A
					ld_indirect_8bit(DE, &A);
					break;
				case 2: // p = 2
					if (cpu->prefix == 0xDD)
						ld_indirect_nn_16bit(&IX);	// LD (nn), IX
					else if (cpu->prefix == 0xFD)
						ld_indirect_nn_16bit(&IY);	// LD (nn), IY
					else
						ld_indirect_nn_16bit(&HL); // LD (nn), HL
					break;
				case 3: // p = 3
					// LD (nn), A
					ld_indirect_nn_8bit(&A);	
					break;
				}
				break;
			case 1: // q = 1
				switch (opcode.p) {
				case 0: // p = 0
					// LD A, (BC)
					ld_8bit_indirect(&A, BC);
					break;
				case 1: // p = 1
					// LD A, (DE)
					ld_8bit_indirect(&A, DE);
					break;
				case 2: // p = 2
					if (cpu->prefix == 0xDD)
						ld_16bit_indirect_nn(&IX);
					else if (cpu->prefix == 0xFD)
						ld_16bit_indirect_nn(&IY);
					else
						ld_16bit_indirect_nn(&HL); // LD HL, (nn)
					break;
				case 3: // p = 3
					// LD A, (nn)
					ld_8bit_indirect_nn(&A);
					break;
				}
				break;
		}
		break;
	case 6: // z = 6
		if (cpu->prefix == 0)
			ld_8bit_n(table_r(opcode.y)); // LD r[y], n
		if (cpu->prefix == 0xDD) {
			ld_indirect_relative_n(IX);	// LD (IX + d), n
		}
		if (cpu->prefix == 0xFD) {
			ld_indirect_relative_n(IY);	// LD (IY + d), n
		}
		break;
	}
}

void execute_x1(opcode_t opcode) {
	if (opcode.z == 6 && opcode.y == 6) { /******** HALT *******/ }
	else {
		// LD r[y], r[z]
		if (cpu->prefix == 0)
			ld_8bit_8bit(table_r(opcode.y), table_r(opcode.z));
		if (cpu->prefix == 0xDD) {
			if (opcode.z == 6) // LD r[y], (IX + d)
				ld_8bit_indirect_relative(table_r(opcode.y), IX);
			else if (opcode.y == 6)
				ld_indirect_relative_8bit(IX, table_r(opcode.z));
		}
		if (cpu->prefix == 0xFD) {
			if (opcode.z == 6) // LD r[y], (IY + d)
				ld_8bit_indirect_relative(table_r(opcode.y), IY);
			else if (opcode.y == 6)
				ld_indirect_relative_8bit(IY, table_r(opcode.z));
		}
	}
}

void execute_x2(opcode_t opcode) {
	alu(opcode.y, table_r(opcode.z));	// ALU OPERATIONS
	if (opcode.z == 6) cpu->ts = 7; // for ALU A, (HL)
}

void execute_x3(opcode_t opcode) {
	
	switch (opcode.z) {
	case 1: // z = 1
		if (opcode.q == 0) { // q = 0
			if (cpu->prefix == 0xDD)
				pop(&IX);						// POP IX
			else if (cpu->prefix == 0xFD)
				pop(&IY);						// POP IY
			else
				pop(table_rp2(opcode.p));		// POP rp2[p]
		}
		else {				// q = 1
			switch (opcode.p) {
			case 0: // p = 0
				break;
			case 1: // p = 1
				exx();			// EXX
				break;
			case 2: // p = 2
				break;
			case 3: // p = 3
				if (cpu->prefix == 0xDD)
					ld_sp_ix();		// LD SP, IX
				else if (cpu->prefix == 0xFD)
					ld_sp_iy();		// LD SP, IY
				else
					ld_sp_hl();		// LD SP, HL
				break;
			}
		}
		break;
	case 3: // z = 3
		switch (opcode.y) {
		case 0: // y = 0
			break;
		case 1: // y = 1
			break;
		case 2: // y = 2
			break;
		case 3: // y = 3
			break;
		case 4: // y = 4
			if (cpu->prefix == 0xDD)
				ex_sp_rr(&IX);
			else if (cpu->prefix == 0xFD)
				ex_sp_rr(&IY);
			else
				ex_sp_rr(&HL); 				// EX (SP), HL
			break;
		case 5: // y = 5		EX DE, HL
			ex_de_hl();
			break;
		case 6: // y = 6
			break;
		case 7: // y = 7
			break;
		}
		break;
	case 5: // z = 5
		if (opcode.q == 0)	{	// q = 0
			if (cpu->prefix == 0xDD)
				push(&IX);					// PUSH IX
			else if (cpu->prefix == 0xFD)
				push(&IY);					// PUSH IY
			else
				push(table_rp2(opcode.p)); // PUSH rp2[p]
		} else {				// q = 1
			// CALL
		}
		break;
	case 6: // z = 6
		alu_n(opcode.y);		// ALU n OPERATIONS
		break;
	}
}


/////////////// ED PREFIXED ////////////////////////
void ed_prefixed(void) {
	
	opcode_t opcode;
	
	cpu->fetch_status = FETCH_INST;
	cpu_fetch();
	
	opcode.byte = IR;
	
	if (opcode.x == 1) {		//	x = 1
		switch (opcode.z) {
		case 3:		// z = 3
			if (opcode.q == 0) // LD (nn), rp[p]
				ld_indirect_nn_16bit(table_rp(opcode.p));
			else // LD rp[p], (nn)
				ld_16bit_indirect_nn(table_rp(opcode.p));
			break;
		case 7:
			switch(opcode.y) {
			case 0: // y = 0
				// LD I, A
				ld_8bit_8bit(&I, &A);
				break;
			case 1: // y = 1
				// LD R, A
				ld_8bit_8bit(&R, &A);
				break;
			case 2: // y = 2
				// LD A, I
				ld_8bit_8bit(&A, &I);
				break;
			case 3: // y = 3
				// LD A, R
				ld_8bit_8bit(&A, &R);
				break;
			}
		}
	} else if (opcode.x == 2) { //  x = 2
		switch (opcode.z) {
		case 0: // z = 0
			switch (opcode.y) {
			case 4: // y = 4
				ldi();			// LDI
				break;
			case 5: // y = 5
				ldd();			// LDD
				break;
			case 6: // y = 6
				ldir();			// LDIR
				break;
			case 7: // y = 7
				lddr();			// LDDR
				break;
			}
			break;
		case 1: // z = 1
			switch (opcode.y) {
			case 4: // y = 4
				cpi();			// CPI
				break;
			case 5: // y = 5
				cpd();			// CPD
				break;
			case 6: // y = 6
				cpir();			// CPIR
				break;
			case 7: // y = 7
				cpdr();			// CPDR
				break;
			}
			break;
		}
	}
}
