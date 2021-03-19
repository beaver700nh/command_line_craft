#ifndef COLOR_PAIRS_HPP
#define COLOR_PAIRS_HPP

struct ColorData {
  const int fg;
  const int bg;
  const int cp;
};

namespace Colors {
  extern ColorData dirt;
  extern ColorData win_brdr;
  extern ColorData btn_hghl;
};

#endif
