#include <ncurses.h>
#include <cstring>

#include "misc.hpp"

void Coords::d_print(WINDOW *win, int row, int col) {
  char buf[100];

  sprintf(buf, "x: %ld, y: %ld", x, y);

  mvwaddstr(win, row,   col, "Coords::d_print():");
  mvwaddstr(win, row+1, col, buf);
}
