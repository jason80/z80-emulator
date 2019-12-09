#ifndef __TABLES_H
#define __TABLES_H

#include "cpu.h"

uint8_t* table_r(int);
uint16_t* table_rp(int);

uint16_t* table_rp_IX(int);
uint16_t* table_rp_IY(int);

uint16_t* table_rp2(int);

int table_cc(int);

#endif
