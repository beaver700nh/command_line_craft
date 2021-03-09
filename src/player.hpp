#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ncurses.h>
#include "gfx_core.hpp"

struct PlayerReprs {
  static const chtype *up1() { FACTORY_RET(ACS_LEQUAL, ACS_GEQUAL); }
  static const chtype *up2() { FACTORY_RET(ACS_LTEE,   ACS_RTEE); }
  static const chtype *dn1() { FACTORY_RET('=',        ACS_RARROW); }
  static const chtype *dn2() { FACTORY_RET(ACS_PLUS,   'o'); }
};

class Player {
  public:
    Player();
    Player(Unit up1, Unit up2, Unit dn1, Unit dn2);
    void draw(WINDOW *win, int row, int col);

    bool standing = true;

  private:
    Unit up1;
    Unit up2;
    Unit dn1;
    Unit dn2;
};

#endif
