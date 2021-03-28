#ifndef COLOR_PAIRS_HPP
#define COLOR_PAIRS_HPP

struct ColorData {
  const int fg;
  const int bg;
  const int cp;
};

namespace Colors {
  extern ColorData win_brdr;
  extern ColorData btn_hghl;
  extern ColorData sect_hdr;
  extern ColorData splash;
  extern ColorData dirt;
};

#endif
