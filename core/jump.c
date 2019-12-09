#include "jump.h"

#include "cpu.h"

void jump(void) {
	cpu_fetch();
	cpu_fetch();
	PC = BR;
	cpu->ts = 10;
}

void jump_conditional(int c) {
	if (c) jump();
}
