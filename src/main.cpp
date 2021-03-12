#include <iostream>
#include <ncurses.h>
#include <cstdlib>

#include "game.hpp"

int main() {
  atexit(end);

  init();

  while (true) {
    if (tick() == -1) {
      break;
    }
  }

  end();

  return 0;
}
