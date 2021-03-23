#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP

#include "../game.hpp"

namespace ActionMove {
  constexpr int up    = 0x11;
  constexpr int down  = 0x12;
  constexpr int left  = 0x13;
  constexpr int right = 0x14;
};

namespace ActionMisc {
  constexpr int idle  = 0x21;
  constexpr int quit  = 0x22;
  constexpr int other = 0x23;
};

namespace ActionInteract {
  constexpr int press = 0x31;
  constexpr int flick = 0x32;
  constexpr int inven = 0x33;
  constexpr int chest = 0x34;
  constexpr int door  = 0x35;
  constexpr int sleep = 0x36;
};

namespace ActionSelect {
  constexpr int sel_up    = 0x41;
  constexpr int sel_down  = 0x42;
  constexpr int sel_left  = 0x43;
  constexpr int sel_right = 0x44;

  constexpr int mv_up     = 0x51;
  constexpr int mv_down   = 0x52;
  constexpr int mv_left   = 0x53;
  constexpr int mv_right  = 0x54;

  constexpr int sel_ok = 0x61;
};

namespace ActionChat {
  constexpr int focus = 0x71;
  constexpr int cmd   = 0x72;
  constexpr int send  = 0x73;
  constexpr int unfcs = 0x74;
};

int handle_keypress(int ch, AppState st, FocusType fc);

#endif
