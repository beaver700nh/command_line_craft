#include <cstring>
#include <ncurses.h>
#include <string>
#include <unordered_map>

#include "gfx_core.hpp"
#include "gui.hpp"

MenuButton::MenuButton() {
  /* default ctor does nothing */;
}

MenuButton::MenuButton(int row, int col, int width, int height, const char *text, int id, bool centered, int attrs) {
  this->row = row;
  this->col = col;
  this->width = width;
  this->height = height;
  this->text = text;
  this->id = id;
  this->attrs = attrs;
  this->centered = centered;
}

void MenuButton::draw(WINDOW *win, bool hghl, int row_offset, int col_offset) {
  attron(attrs);
  draw_btn(
    win, row_offset + row, col_offset + col, width, height, 
    height / 2, (centered ? (width - strlen(text)) / 2 : 1), text, hghl
  );
  attroff(attrs);
}

MenuHeader::MenuHeader() {
  /* default ctor does nothing */;
}

MenuHeader::MenuHeader(int row, int col, const char *text, MHType type, int attrs) {
  this->row = row;
  this->col = col;
  this->text = text;
  this->type = type;
  this->attrs = attrs;
}

void MenuHeader::draw(WINDOW *win, int row_offset, int col_offset) {
  if (type == MHType::FILE) {
    draw_txt(win, row, col, text, attrs);
  }
  else if (type == MHType::TEXT) {
    attron(attrs);
    mvwaddstr(win, row, col, text);
    attroff(attrs);
  }
  else {
    mvwaddstr(win, row, col, "Error: unknown MHType");
  }
}

MenuScreen::MenuScreen() {
  /* default ctor does nothing */;
}

MenuScreen::MenuScreen(MenuHeader header) {
  set_header(header);
}

MenuScreen::MenuScreen(std::vector<MenuButton> buttons) {
  this->buttons = std::vector<MenuButton>(buttons);
}

MenuScreen::MenuScreen(std::vector<MenuButton> buttons, std::vector<std::unordered_map<int, int>> layout) {
  this->buttons = std::vector<MenuButton>(buttons);
  set_layout(layout);
}

MenuScreen::MenuScreen(MenuHeader header, std::vector<MenuButton> buttons, std::vector<std::unordered_map<int, int>> layout) {
  this->buttons = std::vector<MenuButton>(buttons);
  set_layout(layout);
  set_header(header);
}

void MenuScreen::set_header(MenuHeader header) {
  this->header = header;
}

void MenuScreen::add_button(MenuButton button) {
  buttons.push_back(button);
}

int MenuScreen::get_button(int direction, int id) {
  if (id == -1) {
    id = highlighted;
  }

  if (id >= layout.size()) {
    return id;
  }

  return layout.at(id)[direction];
}

void MenuScreen::highlight(int id) {
  highlighted = id;
}

void MenuScreen::set_layout(std::vector<std::unordered_map<int, int>> layout) {
  this->layout = std::vector<std::unordered_map<int, int>>(layout);
}

void MenuScreen::draw(WINDOW *win, int row, int col, bool border) {
  if (border) {
    int rows, cols;
    getmaxyx(win, rows, cols);

    draw_box(win, row, col, cols, rows);
  }

  header.draw(win, row, col);

  for (auto b : buttons) {
    b.draw(win, (b.id == highlighted), row, col);
  }
}
