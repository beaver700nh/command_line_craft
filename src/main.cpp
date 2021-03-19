#include <iostream>
#include <ncurses.h>
#include <cstdlib>

#include "game.hpp"

int main() {
  atexit(end);

  init();

  while (tick() != -1);

  end();

  return 0;
}
