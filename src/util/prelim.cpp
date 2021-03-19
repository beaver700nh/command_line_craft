#include <ncurses.h>
#include <locale>

#include "prelim.hpp"
#include "../data/colors.hpp"

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

void curses_init_pairs() {
  init_pair(Colors::win_brdr.cp, Colors::win_brdr.fg, Colors::win_brdr.bg);
  init_pair(Colors::btn_hghl.cp, Colors::btn_hghl.fg, Colors::btn_hghl.bg);
}
