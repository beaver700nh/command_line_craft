#include <ncurses.h>

#include "colors.hpp"

namespace Colors {
  ColorData dirt     {.fg = 0x00, .bg = 0x3A, .cp = 2};
  ColorData win_brdr {.fg = 0xE8, .bg = 0x08, .cp = 1};
  ColorData btn_hghl {.fg = 0xE2, .bg = 0x08, .cp = 3};
};
