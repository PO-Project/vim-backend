
#include "VimBackend.hpp"

#include <ncurses.h>

namespace backends
{

void VimBackend::operator()()
{
    initscr();
	printw("Hello World!");
	refresh();
	getch();
	endwin();
}

}
