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

  world = World(1);

  gamewin = newwin(24, 48, 5, 10);
  getmaxyx(gamewin, GW_ROWS, GW_COLS);

  debugwin = newwin(3, 52, 1, 8);
}

int input() {
	int ch;
 
  if ((ch = wgetch(gamewin)) != ERR) {
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
  }

	return 0;
}

void output() {
	werase(gamewin);
	werase(debugwin);

  coords.d_print(debugwin, 1, 3);
  world.plane.d_print(debugwin, 1, 30);

	wborder(gamewin, 0, 0, 0, 0, 0, 0, 0, 0);

  player.draw(gamewin, GW_ROWS / 2, GW_COLS / 2);

  wrefresh(gamewin);
	wrefresh(debugwin);
}

int tick() {
  using namespace std::this_thread;
  using namespace std::chrono;

  time_point<system_clock> next_tick = system_clock::now() + microseconds(US_PER_SEC / TARGET_FPS);

	int retval;
	if ((retval = input()) != 0) {
		return retval;
	}

	output();

	sleep_until(next_tick);

  return 0;
}

void end() {
  curs_set(1);
  echo();
  nocbreak();
  endwin();
}
