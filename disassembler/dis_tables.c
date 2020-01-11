#include "dis_tables.h"

#include <string.h>

void table_rp(int op, char* reg) {
	switch (op) {
		case 0:
			strcpy(reg, "BC");
			break;
		case 1:
			strcpy(reg, "DE");
			break;
		case 2:
			strcpy(reg, "HL");
			break;
		case 3:
			strcpy(reg, "SP");
			break;
	}
}

void table_rp_IX(int op, char* reg) {
	table_rp(op, reg);
	if (op == 2) strcpy(reg, "IX");
}

void table_rp_IY(int op, char* reg) {
	table_rp(op, reg);
	if (op == 2) strcpy(reg, "IY");
}


void table_r(int op, char* reg) {
	switch (op) {
		case 0: strcpy(reg, "B");
			break;
		case 1: strcpy(reg, "C");
			break;
		case 2: strcpy(reg, "D");
			break;
		case 3: strcpy(reg, "E");
			break;
		case 4: strcpy(reg, "H");
			break;
		case 5: strcpy(reg, "L");
			break;
		case 6: strcpy(reg, "(HL)");
			break;
		case 7: strcpy(reg, "A");
			break;
	}
}

void table_alu_op(int op, char* str) {
	switch(op) {
	case 0:		// ADD
		strcpy(str, "ADD A,");
		break;
	case 1:		// ADC
		strcpy(str, "ADC A,");
		break;
	case 2:		// SUB
		strcpy(str, "SUB");	
		break;
	case 3:		// SBC
		strcpy(str, "SBC A,");
		break;
	case 4:		// AND
		strcpy(str, "AND");
		break;
	case 5:		// XOR
		strcpy(str, "XOR");
		break;
	case 6:		// OR
		strcpy(str, "OR");
		break;
	case 7:		// CP
		strcpy(str, "CP");
		break;
	}
}

void table_cc(int op, char* str) {
	switch (op) {
		case 0:
			strcpy(str, "NZ");
			break;
		case 1:
			strcpy(str, "Z");
			break;
		case 2:
			strcpy(str, "NC");
			break;
		case 3:
			strcpy(str, "C");
			break;
		case 4:
			strcpy(str, "PO");
			break;
		case 5:
			strcpy(str, "PE");
			break;
		case 6:
			strcpy(str, "P");
			break;
		case 7:
			strcpy(str, "M");
			break;
	}
}
