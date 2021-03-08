#include <iostream>
#include <ncurses.h>

#include "game.hpp"

#include "colortest.hpp"

int main() {
  // colortest();
  // return 0;

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
