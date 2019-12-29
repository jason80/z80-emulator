#include <ncurses.h>

int main(int argc, char** argv) {
	initscr();
	start_color();
	
	printw("Z80 Cross Platform Emulator\n");
	refresh();
	getch();
	
	endwin();
	
	return 0;
}
