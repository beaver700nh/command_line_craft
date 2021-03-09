#include <ncurses.h>

void colortest() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  curs_set(0);
  start_color();

  for (int n = 1; n < 256; ++n) {
    init_pair(n, n, n);
  }

  init_pair(0, -1, -1);

  for (int row = 0; row < 16; ++row) {
    for (int col = 0; col < 16; ++col) {
      mvaddch(row + 1, col + 1, ' ' | COLOR_PAIR((row << 4) + col));
      refresh();
    }
  }

  for (int group = 0; group < 12; ++group) {
    for (int member = 0; member < 18; ++member) {
      mvaddch(group + 1, member + 25, ' ' | COLOR_PAIR(group * 18 + member + 16));
      refresh();
    }
  }

  for (int member = 0; member < 16; ++member) {
    mvaddch(14, 25 + member, ' ' | COLOR_PAIR(member));
  }

  for (int member = 232; member < 240; ++member) {
    mvaddch(16, 25 + (member - 232), ' ' | COLOR_PAIR(member));
  }

  for (int member = 240; member < 255; ++member) {
    mvaddch(16, 33 + (member - 240), ' ' | COLOR_PAIR(member));
  }

  refresh();

  while (1) {;}

  curs_set(1);
  endwin();
}

int main() {
  colortest();
  return 0;
}
