#include "tables.h"

uint8_t* table_r(int v) {
	switch (v) {
		case 0: return &B;
		case 1: return &C;
		case 2: return &D;
		case 3: return &E;
		case 4: return &H;
		case 5: return &L;
		case 6: return &cpu->mem[HL];
		case 7: return &A;
		default: return 0;
	}
}

uint16_t* table_rp(int v) {
	switch (v) {
		case 0: return &BC;
		case 1: return &DE;
		case 2: return &HL;
		case 3: return &SP;
		default: return 0;
	}
}

uint16_t* table_rp_IX(int v) {
	switch (v) {
		case 0: return &BC;
		case 1: return &DE;
		case 2: return &IX;
		case 3: return &SP;
		default: return 0;
	}
}

uint16_t* table_rp_IY(int v) {
	switch (v) {
		case 0: return &BC;
		case 1: return &DE;
		case 2: return &IY;
		case 3: return &SP;
		default: return 0;
	}
}

uint16_t* table_rp2(int v) {
	switch(v) {
		case 0: return &BC;
		case 1: return &DE;
		case 2: return &HL;
		case 3: return &AF;
		default: return 0;
	}
}
