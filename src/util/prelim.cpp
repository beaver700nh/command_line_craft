#include <ncurses.h>
#include <locale>

#include "prelim.hpp"

void curses_init_seq() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  refresh();
}

void curses_init_win(WINDOW *win) {
  keypad(win, true);
  nodelay(win, true);
}
