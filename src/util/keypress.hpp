#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP

namespace ActionMove {
  constexpr int up    = 0x11;
  constexpr int down  = 0x12;
  constexpr int left  = 0x13;
  constexpr int right = 0x14;
};

namespace ActionMisc {
  constexpr int other = 0;
  constexpr int quit = -1;
}

int handle_keypress(int ch);

#endif
