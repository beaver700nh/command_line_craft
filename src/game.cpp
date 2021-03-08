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

#define ESC 27

#define US_PER_SEC 1000000
#define TARGET_FPS 60

Coords coords;
Player player;
World  world;
// Plane<int> plane;

void init() {
  curses_init_seq();

  player = Player(
    stdscr,
    Unit(PlayerReprs::up1(), 0), Unit(PlayerReprs::up2(), 0), \
    Unit(PlayerReprs::dn1(), 0), Unit(PlayerReprs::dn2(), 0)
  );

  world = World(1);

  // plane = Plane<int>(1, 3, 5);
}

int tick() {
  using namespace std::this_thread;
  using namespace std::chrono;

  time_point<system_clock> next_tick = system_clock::now() + microseconds(US_PER_SEC / TARGET_FPS);

  int ch;

  clear();

  if ((ch = getch()) != ERR) {
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

  /* TODO: draw world */;

  player.draw(5, 15);
  // world.draw(stdscr, 0, 0);

  world.draw(stdscr, 0, 0);

  coords.d_print(stdscr, 1, 20);
  world.plane.d_print(stdscr, 1, 40);
  // plane.d_print(stdscr, 1, 40);

  refresh();

  sleep_until(next_tick);

  return 0;
}

void end() {
  endwin();
}
