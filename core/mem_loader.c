#include "mem_loader.h"

#include <stdio.h>
#include "cpu.h"

void load_memory(uint16_t start, char* filename) {
	FILE* file = fopen(filename, "rb");
	
	while (!feof(file)) {
		fread(&cpu->mem[start], 1, 1, file);
		start ++;
	}
	
	fclose(file);
}
