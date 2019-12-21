#include "call_ret.h"

#include "cpu.h"
#include "stack.h"

void call(void) {
	cpu_fetch();
	cpu_fetch();
	
	push_word(PC);
	
	PC = BR;
	
	cpu->ts = 17;
}
