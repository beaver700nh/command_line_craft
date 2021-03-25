#ifndef GUI_HPP
#define GUI_HPP

#include <ncurses.h>
#include <vector>

enum class MHType {NONE, FILE, TEXT};

class MenuButton {
  public:
    MenuButton();
    MenuButton(int row, int col, int width, int height, const char *text, int id, bool centered, int attrs = 0);

    void draw(WINDOW *win, bool hghl, int row_offset = 0, int col_offset = 0);

    int row, col, width, height, id, attrs;
    const char *text;
    bool centered;
};

class MenuHeader {
  public:
    MenuHeader();
    MenuHeader(int row, int col, const char *text, MHType type, int attrs = 0);

    void draw(WINDOW *win, int row_offset = 0, int col_offset = 0);

    int row, col, attrs;
    MHType type;
    const char *text;
};

class MenuScreen {
  public:
    MenuScreen();
    MenuScreen(MenuHeader header);
    MenuScreen(std::vector<MenuButton> buttons);
    MenuScreen(std::vector<MenuButton> buttons, std::vector<std::unordered_map<int, int>> layout);
    MenuScreen(MenuHeader header, std::vector<MenuButton> buttons, std::vector<std::unordered_map<int, int>> layout);

    void set_header(MenuHeader header);
    void add_button(MenuButton button);
    int  get_button(int direction, int id = -1);
    void highlight(int id);
    bool highlighting(int id);
    int  highlighted();
    void set_layout(std::vector<std::unordered_map<int, int>> layout);

    void draw(WINDOW *win, int row, int col, bool border = false);

  private:
    MenuHeader header;

    int highlighted_ = 0;

    std::vector<MenuButton> buttons;
    std::vector<std::unordered_map<int, int>> layout;
};

#endif
