#include <cstring>
#include <ncurses.h>

#include "entity.hpp"
#include "gfx_core.hpp"
#include "player.hpp"

Player::Player() {
  /* default ctor does nothing */;
}

Player::Player(Unit up1, Unit up2, Unit dn1, Unit dn2) {
  this->up1 = up1;
  this->up2 = up2;
  this->dn1 = dn1;
  this->dn2 = dn2;
}

void Player::draw(WINDOW *win, int row, int col, bool should_offset) {
  if (standing) {
    up1.draw(win, row-1, col, should_offset);
    up2.draw(win, row,   col, should_offset);
  }
  else {
    dn1.draw(win, row, col,   should_offset);
    dn2.draw(win, row, col+1, should_offset);
  }
}
