#include <ncurses.h>
#include <sstream>

#include "misc.hpp"

#include "debug_print.hpp"

void d_print_coords(int row, int col, Coords *coords) {
  std::stringstream ss_x;
  ss_x << "x: " << coords->x;

  std::stringstream ss_y;
  ss_y << "y: " << coords->y;

  mvaddstr(row,   col, "d_print_coords (0, 0 relative):");
  mvaddstr(row+1, col, ss_x.str().c_str());
  mvaddstr(row+2, col, ss_y.str().c_str());
}
