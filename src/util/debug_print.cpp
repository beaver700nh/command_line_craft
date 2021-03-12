#include <ncurses.h>
#include <sstream>

#include <ncurses.h>

#include "debug_print.hpp"

void d_print_maxwin(WINDOW *win, int row, int col, WINDOW *to_test) {
  int rows, cols;
  getmaxyx(to_test, rows, cols);

  char buf[50];
  sprintf(buf, "maxy: %d, maxx: %d", rows, cols);

  mvwaddstr(win, row,   col, "d_print_maxwin():");
  mvwaddstr(win, row+1, col, buf);
}
