#ifndef MISC_HPP
#define MISC_HPP

#include <ncurses.h>
#include <random>

#define fill_constants(rows, cols, ctrr, ctrc, ctrx, ctry) (ctrr = rows/2, ctrc = cols/2, ctry = ctrr, ctrx = ctrc/2)

#define dwborder(win) box(win, 0, 0)

enum {UP, DOWN, LEFT, RIGHT};

class Coords {
  public:
    Coords();
    Coords(Coords &coords);
    Coords(long x, long y);

    long x = 0, y = 0;
    void d_print(WINDOW *win, int row, int col);
};

void unicode_to_chtype(const char *bytes, chtype *decoded);
chtype decode_lookup(char b);

int get_rand_num(int min, int outcomes, std::mt19937 rng);

int set_logo(char *dest, std::mt19937 rng);
int set_splash(char *dest, std::mt19937 rng);

#endif
