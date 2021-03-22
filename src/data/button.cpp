#include "../game.hpp"
#include "colors.hpp"
#include <ncurses.h>

#include "button.hpp"

const char btn_labels[][50][30] = {
  /* main menu */
  {
    "     Play     ",
    "    Options   ",
    "     Quit     ",
  },
  /* options main */
  {
    "     Music: xx%     ",
    " Sound Effects: xx% ",
    "  Invert Mouse: xxx ",
    " Difficulty: xxxxxx ",
    "         TBD        ",
    "     Controls...    ",
    "   Texture Packs... ",
    "     Recipes...     ",
    "    Color Packs...  ",
    "      Items...      ",
    "  Back to Main Menu "
  },
};

int get_up_btn(int cur_btn, AppState st) {
  if (st == MAIN_MENU) {
    if (cur_btn == 0) {
      return 2;
    }
    else {
      return cur_btn - 1;
    }
  }
  else if (st == OPTIONS) {
    if (cur_btn == 0 || cur_btn == 1) {
      return 10;
    }
    else {
      return cur_btn - 2;
    }
  }

  return cur_btn;
}

int get_down_btn(int cur_btn, AppState st) {
  if (st == MAIN_MENU) {
    if (cur_btn == 2) {
      return 0;
    }
    else {
      return cur_btn + 1;
    }
  }
  else if (st == OPTIONS) {
    if (cur_btn == 8 || cur_btn == 9) {
      return 10;
    }
    else if (cur_btn == 10) {
      return 0;
    }
    else {
      return cur_btn + 2;
    }
  }

  return cur_btn;
}

int get_left_btn(int cur_btn, AppState st) {
  if (st == OPTIONS) {
    if (cur_btn == 10) {
      return 10;
    }
    else if (cur_btn % 2 == 0) { // even numbers (on the left)
      return cur_btn + 1;
    }
    else { // odd numbers (on the right)
      return cur_btn - 1;
    }
  }

  return cur_btn;
}

int get_right_btn(int cur_btn, AppState st) {
  if (st == OPTIONS) {
    if (cur_btn == 10) {
      return 10;
    }
    else if (cur_btn % 2 == 0) { // even numbers (on the left)
      return cur_btn + 1;
    }
    else { // odd numbers (on the right)
      return cur_btn - 1;
    }
  }

  return cur_btn;
}
