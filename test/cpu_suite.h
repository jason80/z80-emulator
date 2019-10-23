#ifndef __CPU_SUITE_H
#define __CPU_SUITE_H

int init_cpu_suite(void);
int clean_cpu_suite(void);

void endian_test(void);
void register_test(void);

void fetch_test(void);

void flags_test(void);

#endif
