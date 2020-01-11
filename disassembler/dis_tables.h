#ifndef __DIST_TABLES_H
#define __DIST_TABLES_H

void table_rp(int op, char* code);

void table_rp_IX(int op, char* reg);
void table_rp_IY(int op, char* reg);

void table_r(int op, char* reg);

void table_alu_op(int op, char* str);

void table_cc(int op, char* str);

#endif
