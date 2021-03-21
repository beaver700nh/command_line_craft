#include <ncurses.h>

#include "colors.hpp"

namespace Colors {
  ColorData win_brdr {.fg = 0xE8, .bg = 0x08, .cp = 1};
  ColorData btn_hghl {.fg = 0xE2, .bg = 0x08, .cp = 2};
  ColorData sect_hdr {.fg = 0xE6, .bg = 0x08, .cp = 3};
  ColorData dirt     {.fg = 0x00, .bg = 0x3A, .cp = 4};
};
