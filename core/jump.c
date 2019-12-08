#include "jump.h"

#include "cpu.h"

void jump(void) {
	cpu_fetch();
	cpu_fetch();
	PC = BR;
	cpu->ts = 10;
}
