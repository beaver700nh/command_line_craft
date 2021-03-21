#include <iostream>
#include <ncurses.h>
#include <cstdlib>

#include "game.hpp"

int main() {
  atexit(end);

  int result = init();

  if (result == 0) {
    while (tick() != -1);
  }
  else {
    end();

    if (result == -1) {
      std::cout << "main.cpp: error: Terminal does not support colors.\n";
    }
    else if (result == -2) {
      std::cout << "main.cpp: error: Unable to start colors.\n";
    }
    else {
      std::cout << "main.cpp: error: Unknown error happened.\n";
    }
  }

  return 0;
}
