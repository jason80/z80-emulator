#ifndef __STACK_H
#define __STACK_H

#include <inttypes.h>

void push_byte(uint8_t byte);
uint8_t pop_byte(void);

void push_word(uint16_t word);
uint16_t pop_word(void);

#endif

