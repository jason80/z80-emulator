#include "stack.h"

#include "cpu.h"

void push_byte(uint8_t byte) {
	SP --;
	ADR = SP; DATA = byte;
}

uint8_t pop_byte(void) {
	ADR = SP; SP ++;
	return DATA;
}

void push_word(uint16_t word) {
	word_t w;
	w.word = word;
	push_byte(w.h);
	push_byte(w.l);
}

uint16_t pop_word(void) {
	word_t w;
	w.l = pop_byte();
	w.h = pop_byte();
	
	return w.word;
}
