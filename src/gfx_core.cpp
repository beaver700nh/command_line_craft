#include <chrono>
#include <cstring>
#include <iostream>
#include <ncurses.h>
#include <sstream>

#include "world.hpp"
#include "gfx_core.hpp"

/*************** Unit ***************/

Unit::Unit() {
  /* default ctor does nothing */;
}

Unit::Unit(const chtype *repr, int color_pair) {
  ctor_helper(repr, color_pair);
}

Unit::Unit(const chtype *repr, int color_pair, int fg, int bg) {
  init_pair(color_pair, fg, bg);
  ctor_helper(repr, color_pair);
}

Unit::Unit(const char *repr, int color_pair) {
  ctor_helper(repr, color_pair);
}

Unit::Unit(const char *repr, int color_pair, int fg, int bg) {
  init_pair(color_pair, fg, bg);
  ctor_helper(repr, color_pair);
}

void Unit::ctor_helper(const chtype *repr, int color_pair) {
  memcpy(this->wrepr, repr, (sizeof repr) * 3);
  this->wrepr[2] = '\0';
  this->color_pair = color_pair;

  this->is_wide = true;
}

void Unit::ctor_helper(const char *repr, int color_pair) {
  memcpy(this->nrepr, repr, (sizeof repr) * 3);
  this->nrepr[2] = '\0';
  this->color_pair = color_pair;

  this->is_wide = false;
}

void Unit::draw(WINDOW *win, int row, int col, bool should_offset) {
  float offset = (should_offset ? 0.5 : 0);

  wattron(win, COLOR_PAIR(color_pair));

  if (is_wide) {
    s_mvwaddch(win, row + offset * 2, col + offset,       wrepr[0]); // 0.5 * 2 = 1
    s_mvwaddch(win, row + offset * 2, col + offset + 0.5, wrepr[1]); // 0.5 becomes 1 bc cols are scaled
  }
  else {
    s_mvwaddstr(win, row + offset * 2, col + offset, nrepr);
  }

  wattroff(win, COLOR_PAIR(color_pair));
}

/*************** Item ***************/

Item::Item() {
  /* default ctor does nothing */;
}

Item::Item(int row, int col, Unit unit, int type, WINDOW *win) {
  this->row = row;
  this->col = col;

  this->unit = unit;

  this->type = type;

  this->win = win;
}

int Item::handle(int ch) {
  updated = true;
  return 0;
}

void Item::draw() {
  if (updated) {
    unit.draw(win, row, col);

    updated = false;
  }
}

void Item::tick() {
  static bool waiting = false;
  static std::chrono::time_point<std::chrono::system_clock> waiting_for;

  if (type & GRAVITY) {
    if (true) {
      if (std::chrono::system_clock::now() < waiting_for) {
        move(fall_speed++, 0);
      }
      else {
        waiting_for = std::chrono::system_clock::now() + std::chrono::seconds(1);
        endwin();

        std::time_t now_c = std::chrono::system_clock::to_time_t(waiting_for);
        std::stringstream ss;
        ss << now_c;
        std::cout << ss.str() << "\n";
      }
    }
    else {
      fall_speed = 0;
    }
  }
}

void Item::move(int rows, int cols) {
  row += rows;
  col += cols;

  if (rows != 0 || cols != 0) {
    updated = true;
  }
}

void draw_box(WINDOW *win, int r, int c, int w, int h) {
  mvwaddch(win, r,     c,     ACS_ULCORNER);
  mvwaddch(win, r,     c+w-1, ACS_URCORNER);
  mvwaddch(win, r+h-1, c,     ACS_LLCORNER);
  mvwaddch(win, r+h-1, c+w-1, ACS_LRCORNER);

  mvwhline(win, r,     c+1,   ACS_HLINE, w-2);
  mvwhline(win, r+h-1, c+1,   ACS_HLINE, w-2);
  mvwvline(win, r+1,   c,     ACS_VLINE, h-2);
  mvwvline(win, r+1,   c+w-1, ACS_VLINE, h-2);
}
