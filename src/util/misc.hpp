#ifndef MISC_HPP
#define MISC_HPP

#include <ncurses.h>

class Coords {
  public:
    long x = 0, y = 0;
    void d_print(WINDOW *win, int row, int col);
};

#endif
