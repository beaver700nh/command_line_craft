#include <iostream>
#include <ncurses.h>
#include <cstdlib>

#include "game.hpp"

int main() {
  atexit(end);

  init();

  while (true) {
    int result = tick();

    if (result == -1) {
      break;
    }
  }

  end();

  return 0;
}
