#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP

namespace ActionMove {
  constexpr int up    = 0x11;
  constexpr int down  = 0x12;
  constexpr int left  = 0x13;
  constexpr int right = 0x14;
};

namespace ActionMisc {
  constexpr int idle  = 0;
  constexpr int quit  = -1;
  constexpr int other = -2;
};

namespace ActionInteract {
  constexpr int press = 0;
  constexpr int flick = 1;
  constexpr int inven = 2;
  constexpr int chest = 3;
  constexpr int door  = 4;
  constexpr int sleep = 5;
};

int handle_keypress(int ch);

#endif
