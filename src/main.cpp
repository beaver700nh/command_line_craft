#include <iostream>
#include <ncurses.h>
#include <cstdlib>

#include "game.hpp"

int main() {
  atexit(end);

  int tick_result;

  int result = init();

  if (result == 0) {
    while ((tick_result = tick()) == 0);
  }
  else {
    end();

    std::cout << "\n";

    if (result == -1) {
      std::cout << "main.cpp: error: Terminal does not support colors.\n";
    }
    else if (result == -2) {
      std::cout << "main.cpp: error: Unable to start colors.\n";
    }
    else if (result == -3) {
      std::cout << "main.cpp: error: Logo failure.\n";
    }
    else if (result == -4) {
      std::cout << "main.cpp: error: Splash text failure.\n";
    }
    else {
      std::cout << "main.cpp: error: Unknown error happened.\n";
    }
  }

  return 0;
}
