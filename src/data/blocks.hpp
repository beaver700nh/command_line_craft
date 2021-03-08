#include <ncurses.h>

#include "../gfx_core.hpp"

namespace Blocks {
  struct Dirt {
    static const chtype *repr() { FACTORY_RET('1', '0'); }
  };
};
