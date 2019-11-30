#include "execute.h"

#include "cpu.h"
#include "tables.h"
#include "load.h"
#include "exchange.h"
#include "block_transfer.h"
#include "search.h"
#include "alu.h"
#include "misc.h"
#include "arithm16.h"
#include "rot_shift.h"

void execute_x0(opcode_t);
void execute_x1(opcode_t);
void execute_x2(opcode_t); // alu
void execute_x3(opcode_t);

void ed_prefixed(void);
void cb_prefixed(void);

void cpu_execute(void) {
	opcode_t opcode;
	
	if (0xDD == IR || 0xFD == IR) {
		cpu->prefix = IR;
		cpu->fetch_status = FETCH_INST;
		cpu_fetch();
	}
	
	opcode.byte = IR;
	
	if (0xED == IR) ed_prefixed();
	else if (0xCB == IR) cb_prefixed();
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
			cpu->ts = 4;	// NOP
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
					ld_16bit_nn(&IX);				// LD IX, nn
				else if (cpu->prefix == 0xFD)
					ld_16bit_nn(&IY);				// LD IY, nn
				else
					ld_16bit_nn(table_rp(opcode.p)); // LD rp[p], nn
				break;
			case 1:
				if (cpu->prefix == 0xDD)
					add16(&IX, table_rp_IX(opcode.p));	// ADD IX, rpIX[p]
				else if (cpu->prefix == 0xFD)
					add16(&IY, table_rp_IY(opcode.p));	// ADD IY, rpIY[p]
				else
					add16(&HL, table_rp(opcode.p));		// ADD HL, rp[p]
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
		
	case 3: // z = 3
	
		if (opcode.q == 0) {	// q = 0
			if (cpu->prefix == 0)
				inc_dec_16(table_rp(opcode.p), 1);	// INC rp[p]
			else if (cpu->prefix == 0xDD)
				inc_dec_16(&IX, 1);					// INC IX
			else if (cpu->prefix == 0xFD)
				inc_dec_16(&IY, 1);					// INC IY
		} else {
			if (cpu->prefix == 0) // q = 1
				inc_dec_16(table_rp(opcode.p), -1);	// DEC rp[p]
			else if (cpu->prefix == 0xDD)
				inc_dec_16(&IX, -1);				// DEC IX
			else if (cpu->prefix == 0xFD)
				inc_dec_16(&IY, -1);				// DEC IY
		}
		
		break;
		
	case 4: // z = 4
	
		if (cpu->prefix == 0xDD) {
			if (opcode.y == 6)
				inc_relative(IX);		// INC (IX + d)
		} else if (cpu->prefix == 0xFD) {
			if (opcode.y == 6)
				inc_relative(IY);		// INC (IX + d)
		} else {	
			inc(table_r(opcode.y));		// INC r
			if (opcode.y == 6) cpu->ts = 11;	// for INC (HL)
		}
		break;
		
	case 5: // z = 5
	
		if (cpu->prefix == 0xDD) {
			if (opcode.y == 6)
				dec_relative(IX);		// DEC (IX + d)
		} else if (cpu->prefix == 0xFD) {
			if (opcode.y == 6)
				dec_relative(IY);		// DEC (IX + d)
		} else {	
			dec(table_r(opcode.y));		// DEC r
			if (opcode.y == 6) cpu->ts = 11;	// for DEC (HL)
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
		
	case 7: // z = 7
		switch (opcode.y) {
		case 0:
			rlca();			// RLCA
			break;
		case 1:
			rrca();			// RRCA
			break;
		case 2:
			rla();			// RLA
			break;
		case 3:
			rra();			// RRA
			break;
		case 4: // y = 4
			daa();			// DAA
			break;
		case 5: // y = 5
			cpl();			// CPL
			break;
		case 6: // y = 6
			scf();			// SCF
			break;
		case 7: // y = 7
			ccf();			// CCF
			break;
		}
		break;
	}
}

void execute_x1(opcode_t opcode) {
	if (cpu->prefix == 0) {
		if (opcode.z == 6 && opcode.y == 6) {
			cpu->halt = 1;										// HALT
			cpu->ts = 4;
		} else
			ld_8bit_8bit(table_r(opcode.y), table_r(opcode.z)); // LD r[y], r[z]
	} else if (cpu->prefix == 0xDD) {
		if (opcode.z == 6)
			ld_8bit_indirect_relative(table_r(opcode.y), IX); // LD r[y], (IX + d)
		else if (opcode.y == 6)
			ld_indirect_relative_8bit(IX, table_r(opcode.z));	// LD (IX + d), r[z]
	} else if (cpu->prefix == 0xFD) {
		if (opcode.z == 6)
			ld_8bit_indirect_relative(table_r(opcode.y), IY); // LD r[y], (IY + d)
		else if (opcode.y == 6)
			ld_indirect_relative_8bit(IY, table_r(opcode.z)); // LD (IY + d), r[z]
	}
}

void execute_x2(opcode_t opcode) {
	
	if (cpu->prefix == 0xDD) {
		if (opcode.z == 6)
			alu_indirect(opcode.y, &IX);	// ALU A, (IX + d)
	} else if (cpu->prefix == 0XFD) {
		if (opcode.z == 6)
			alu_indirect(opcode.y, &IY);	// ALU A, (IY + d)
	} else {
		alu(opcode.y, table_r(opcode.z));	// ALU OPERATIONS
		if (opcode.z == 6)
			cpu->ts = 7; // for ALU A, (HL)
	}
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

/////////////// CB PREFIXED ////////////////////////
void cb_prefixed(void) {
	opcode_t opcode;
	
	cpu->fetch_status = FETCH_INST;
	cpu_fetch();
	
	opcode.byte = IR;
	
	if (cpu->prefix == 0xDD || cpu->prefix == 0xFD) {
		cpu_fetch();
		opcode.byte = BRL;
		BRL = IR;
	}
	
	if (opcode.x == 0) {		// x = 0
		
		switch (opcode.y) {
		case 0:		// y = 0
		
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				rlc_relative(IX);		// RLC (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				rlc_relative(IY);		// RLC (IY + d)
			} else {
				rlc(table_r(opcode.z));		// RLC r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for RLC (HL)
			}
			break;
		case 1:		// y = 1
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				rrc_relative(IX);		// RRC (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				rrc_relative(IY);		// RRC (IY + d)
			} else {
				rrc(table_r(opcode.z));		// RRC r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for RRC (HL)
			}
			break;
		case 2:		// y = 2
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				rl_relative(IX);		// RL (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				rl_relative(IY);		// RL (IY + d)
			} else {
				rl(table_r(opcode.z));		// RL r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for RL (HL)
			}
			break;
		case 3:		// y = 3
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				rr_relative(IX);		// RR (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				rr_relative(IY);		// RR (IY + d)
			} else {
				rr(table_r(opcode.z));		// RR r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for RR (HL)
			}
			break;
		case 4:		// y = 4
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				sla_relative(IX);		// SLA (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				sla_relative(IY);		// SLA (IY + d)
			} else {
				sla(table_r(opcode.z));		// SLA r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for SLA (HL)
			}
			break;
		case 5:		// y = 5
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				sra_relative(IX);		// SRA (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				sra_relative(IY);		// SRA (IY + d)
			} else {
				sra(table_r(opcode.z));		// SRA r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for SRA (HL)
			}
			break;
		
		case 7:		// y = 7
			if (cpu->prefix == 0xDD && opcode.z == 6) {
				srl_relative(IX);		// SRL (IX + d)
			} else if (cpu->prefix == 0xFD && opcode.z == 6) {
				srl_relative(IY);		// SRL (IY + d)
			} else {
				srl(table_r(opcode.z));		// SRL r[z]
				if (opcode.z == 6)
					cpu->ts = 15;	// for SRL (HL)
			}
			break;	
		}
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
		case 2:					// z = 2
			if (opcode.q == 0)
				sbc16(&HL, table_rp(opcode.p));			// SBC HL, rp[p]
			else
				adc16(&HL, table_rp(opcode.p));			// ADC HL, rp[p]
			break;
		case 3:					// z = 3
			if (opcode.q == 0)
				ld_indirect_nn_16bit(table_rp(opcode.p));	// LD (nn), rp[p]
			else
				ld_16bit_indirect_nn(table_rp(opcode.p));	// LD rp[p], (nn)
			break;
		case 4:		// z = 4
			neg();				// NEG
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
