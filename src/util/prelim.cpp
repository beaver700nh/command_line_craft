#include <ncurses.h>
#include <locale>

#include "prelim.hpp"

void curses_init_seq() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  curs_set(0);
  start_color();
}
