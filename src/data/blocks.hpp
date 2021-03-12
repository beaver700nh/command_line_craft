#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <ncurses.h>

struct BlockData {
  const chtype repr[3];
};

namespace Blocks {
  extern BlockData dirt;
};

#endif
