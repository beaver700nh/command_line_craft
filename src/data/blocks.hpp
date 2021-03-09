#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <ncurses.h>
#include <unordered_map>

#include "../gfx_core.hpp"

struct BlockData {
  const chtype repr[3];
};

namespace Blocks {
  extern BlockData dirt;
};

#endif
