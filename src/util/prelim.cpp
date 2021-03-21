#include <ncurses.h>
#include <locale>

#include "prelim.hpp"
#include "../data/colors.hpp"

int curses_init_seq() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  if (!has_colors()) {
    return -1;
  }

  if (start_color() != OK) {
    return -2;
  }

  refresh();

  return 0;
}

void curses_init_win(WINDOW *win) {
  keypad(win, true);
  nodelay(win, true);
}

void curses_init_pairs() {
  init_pair(Colors::win_brdr.cp, Colors::win_brdr.fg, Colors::win_brdr.bg);
  init_pair(Colors::btn_hghl.cp, Colors::btn_hghl.fg, Colors::btn_hghl.bg);
  init_pair(Colors::sect_hdr.cp, Colors::sect_hdr.fg, Colors::sect_hdr.bg);
}
