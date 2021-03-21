#include <ncurses.h>
#include <menu.h>

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  curs_set(0);

  ITEM *item_a = new_item("name_a", "desc_a");
  ITEM *item_b = new_item("name_b", "desc_b");
  ITEM *item_c = new_item("name_c", "desc_c");

  ITEM *items[] = {item_a, item_b, item_c};

  MENU *menu = new_menu(items);
  set_menu_spacing(menu, 2, 0, 0);
  set_menu_mark(menu, ">");

  post_menu(menu);

  refresh();

  getch();

  unpost_menu(menu);
  free_menu(menu);

  for (int i = 0; i < 3; ++i) {
    free_item(items[i]);
  }

  curs_set(1);
  endwin();

  return 0;
}
