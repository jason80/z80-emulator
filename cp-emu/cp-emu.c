#include "cp-emu.h"

#include <ncurses.h>
#include <stdio.h>

#include "../core/cpu.h"
#include "../core/mem_loader.h"

config_t config;

int main(int argc, char** argv) {
	
	// Start cpu
	cpu_init();
	
	// Load config
	if (!load_config(argc, argv)) return 0;
	
	// Start ncurses
	initscr();
	start_color();
	
	
	printw("Z80 Cross Platform Emulator\n");
	refresh();
	getch();
	
	// Deinit ncurses
	endwin();
	
	// Deinit cpu
	cpu_clean();
	
	return 0;
}

int load_config(int argc, char** argv) {
	config.program_start = 0x0A00;
	
	if (argc == 1) {
		printf("Parameters error.\n");
		return 0;
	}
	
	load_memory(config.program_start, argv[1]);
	
	return 1;
}

