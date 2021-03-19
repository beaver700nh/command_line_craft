#ifndef MISC_HPP
#define MISC_HPP

#include <ncurses.h>

#define fill_constants(rows, cols, ctrr, ctrc, ctrx, ctry) (ctrr = rows/2, ctrc = cols/2, ctry = ctrr, ctrx = ctrc/2);

#define dwborder(win) wborder(win, 0, 0, 0, 0, 0, 0, 0, 0)

class Coords {
  public:
    long x = 0, y = 0;
    void d_print(WINDOW *win, int row, int col);
};

#endif
