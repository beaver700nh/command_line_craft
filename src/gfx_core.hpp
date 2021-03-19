#ifndef GFX_CORE_HPP
#define GFX_CORE_HPP

#include <ncurses.h>

#include "scale_macros.hpp"

#define FACTORY_VAL(ch1, ch2) {(ch1), (ch2), '\0'}
#define FACTORY_VAR(ch1, ch2) static const chtype val[3] = {(ch1), (ch2), '\0'};
#define FACTORY_RET(ch1, ch2) FACTORY_VAR((ch1), (ch2)); return val;

#define GRAVITY 0x10
#define INERT   0x01
#define SOLID   0x02
#define JUMP    0x03
#define LIQ_U   0x04
#define LIQ_D   0x05
#define LIQ_L   0x06
#define LIQ_R   0x07

class Unit {
  public:
    Unit();
    Unit(const chtype *repr, int color_pair);
    Unit(const chtype *repr, int color_pair, int fg, int bg);
    Unit(const char *repr, int color_pair);
    Unit(const char *repr, int color_pair, int fg, int bg);

    void ctor_helper(const chtype *repr, int color_pair);
    void ctor_helper(const char *repr, int color_pair);

    void draw(WINDOW *win, int row, int col, bool should_offset = false);

    bool is_wide;
    char nrepr[3];
    chtype wrepr[3];
    int color_pair;
};

class Item {
  public:
    Item();
    Item(int row, int col, Unit unit, int type, WINDOW *win);

    int handle(int ch);
    void draw();
    void tick();
    void move(int rows, int cols);

  private:
    int row, col, type;

    Unit unit;

    bool updated = true;

    int fall_speed = 0;

    WINDOW *win;
};

#endif
