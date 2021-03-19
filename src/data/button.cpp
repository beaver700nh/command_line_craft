#include "../game.hpp"
#include "colors.hpp"
#include <ncurses.h>

#include "button.hpp"

const char btn_labels[][15] = {
  "     Play     ",
  "    Options   ",
  "     Quit     ",
};

int get_prev_btn(int cur_btn, AppState st) {
  if (st == MAIN_MENU) {
    if (cur_btn == 0) {
      return 2;
    }
    else {
      return cur_btn - 1;
    }
  }

  return cur_btn;
}

int get_next_btn(int cur_btn, AppState st) {
  if (st == MAIN_MENU) {
    if (cur_btn == 2) {
      return 0;
    }
    else {
      return cur_btn + 1;
    }
  }

  return cur_btn;
}

void draw_box(WINDOW *win, int row, int col, int width, int height) {
  mvwaddch(win, row,          col,         ACS_ULCORNER);
  mvwaddch(win, row,          col+width-1, ACS_URCORNER);
  mvwaddch(win, row+height-1, col,         ACS_LLCORNER);
  mvwaddch(win, row+height-1, col+width-1, ACS_LRCORNER);

  mvwhline(win, row,          col+1,       ACS_HLINE, width-2);
  mvwhline(win, row+height-1, col+1,       ACS_HLINE, width-2);
  mvwvline(win, row+1,        col,         ACS_VLINE, height-2);
  mvwvline(win, row+1,        col+width-1, ACS_VLINE, height-2);
}

void draw_btn(WINDOW *win, int row, int col, int width, int height, int text_row, int text_col, const char *text, bool hghl) {
  hghl && wattron(win, COLOR_PAIR(Colors::btn_hghl.cp));

  draw_box(win,  row,          col,          width, height);
  mvwaddstr(win, row+text_row, col+text_col, text);

  hghl && wattroff(win, COLOR_PAIR(Colors::btn_hghl.cp));
}
