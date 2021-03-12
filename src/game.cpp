#include <chrono>
#include <ncurses.h>
#include <thread>

#include "game.hpp"
#include "gfx_core.hpp"
#include "player.hpp"
#include "world.hpp"

#include "util/debug_print.hpp"
#include "util/keypress.hpp"
#include "util/prelim.hpp"

#include "data/blocks.hpp"
#include "data/colors.hpp"

#define ESC 27

#define US_PER_SEC 1000000
#define TARGET_FPS 24

Coords coords;
Player player;
World  world;

WINDOW *gamewin;
WINDOW *debugwin;

int GW_ROWS, GW_COLS;

void init() {
  curses_init_seq();

  player = Player(
    Unit(PlayerReprs::up1(), 0), Unit(PlayerReprs::up2(), 0), \
    Unit(PlayerReprs::dn1(), 0), Unit(PlayerReprs::dn2(), 0)
  );

  world = World(3);

  gamewin = newwin(26, 50, 5, 9);
  getmaxyx(gamewin, GW_ROWS, GW_COLS);

  debugwin = newwin(4, 52, 0, 8);

  curses_init_win(gamewin);
  curses_init_win(debugwin);

  curses_init_pairs();
}

int input() {
	int ch = wgetch(gamewin);
  int result = handle_keypress(ch);

  if (result == ActionMisc::quit) {
    return -1;
  }
  else if (result == ActionMove::up) {
    ++coords.y;
  }
  else if (result == ActionMove::left) {
    --coords.x;
  }
  else if (result == ActionMove::down) {
    --coords.y;
  }
  else if (result == ActionMove::right) {
    ++coords.x;
  }
  else if (result == ActionInteract::sleep) {
    player.standing = !player.standing;
  }
  else {
    return -2;
  }

  return 0;
}

void output() {
	werase(gamewin);
	werase(debugwin);

	dwborder(debugwin);

  wattron(gamewin, COLOR_PAIR(Colors::win_brdr.cp));
	dwborder(gamewin);
  wattroff(gamewin, COLOR_PAIR(Colors::win_brdr.cp));

  coords.d_print(debugwin, 1, 3);
  //world.plane.d_print(debugwin, 1, 32);
  d_print_maxwin(debugwin, 1, 32, gamewin);

  world.draw(gamewin, 0, 0, true);

  player.draw(gamewin, GW_ROWS/2 - 2, GW_COLS/4, true);

  wrefresh(gamewin);
	wrefresh(debugwin);
}

int tick() {
  using namespace std::this_thread;
  using namespace std::chrono;

  auto next_tick = steady_clock::now() + microseconds(US_PER_SEC / TARGET_FPS);

	int retval = input();

	output();

	sleep_until(next_tick);

  return retval;
}

void end() {
  curs_set(1);
  echo();
  nocbreak();
  endwin();
}
