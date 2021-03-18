#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP

namespace ActionMove {
  constexpr int up    = 0x11;
  constexpr int down  = 0x12;
  constexpr int left  = 0x13;
  constexpr int right = 0x14;
};

namespace ActionMisc {
  constexpr int idle  = 0x20;
  constexpr int quit  = 0x21;
  constexpr int other = 0x22;
};

namespace ActionInteract {
  constexpr int press = 0x30;
  constexpr int flick = 0x31;
  constexpr int inven = 0x32;
  constexpr int chest = 0x33;
  constexpr int door  = 0x34;
  constexpr int sleep = 0x35;
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

  constexpr int sel_ok = 0x60;
};

int handle_keypress(int ch);

#endif
