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
