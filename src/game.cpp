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
#define TARGET_FPS 30

AppState st = MM_PLAY;

Coords coords;
Player player;
World  world;

WINDOW *gamewin;
WINDOW *debugwin;

chtype default_bkgd;

int GW_ROWS, GW_COLS, GW_CTRY, GW_CTRX, GW_CTRR, GW_CTRC;

void init() {
  curses_init_seq();

  player = Player(
    Unit(PlayerReprs::up1(), 0), Unit(PlayerReprs::up2(), 0), \
    Unit(PlayerReprs::dn1(), 0), Unit(PlayerReprs::dn2(), 0)
  );

  world = World(3);
  world.plane.set_data(0, 0, Unit("%%", 0));

  gamewin = newwin(26, 50, 5, 9);
  getmaxyx(gamewin, GW_ROWS, GW_COLS);
  GW_CTRR = GW_ROWS/2;
  GW_CTRC = GW_COLS/2;
  GW_CTRY = GW_CTRR;
  GW_CTRX = GW_CTRC/2;

  debugwin = newwin(4, 52, 0, 8);

  curses_init_win(gamewin);
  curses_init_win(debugwin);

  curses_init_pairs();

  default_bkgd = getbkgd(gamewin);
  wbkgdset(gamewin, COLOR_PAIR(Colors::win_brdr.cp));
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
  else if (result == ActionSelect::sel_up) {
    if (st == MM_PLAY) {
      st = MM_QUIT;
    }
    else if (st == MM_QUIT) {
      st = MM_OPTIONS;
    }
    else if (st == MM_OPTIONS) {
      st = MM_PLAY;
    }
  }
  else if (result == ActionSelect::sel_down) {
    if (st == MM_PLAY) {
      st = MM_OPTIONS;
    }
    else if (st == MM_OPTIONS) {
      st = MM_QUIT;
    }
    else if (st == MM_QUIT) {
      st = MM_PLAY;
    }
  }
  else if (result == ActionSelect::sel_ok) {
    if (st == MM_PLAY) {
      wbkgdset(gamewin, default_bkgd);
      st = GAME;
    }
    else if (st == MM_OPTIONS) {
      return -1;
    }
    else if (st == MM_QUIT) {
      return -1;
    }
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

  coords.d_print(debugwin, 1, 3);
  // world.plane.d_print(debugwin, 1, 32);
  d_print_maxwin(debugwin, 1, 32, gamewin);

  wattron(gamewin, COLOR_PAIR(Colors::win_brdr.cp));
	dwborder(gamewin);
  wattroff(gamewin, COLOR_PAIR(Colors::win_brdr.cp));

  if (st == GAME) {
    draw_game();
  }
  else if (st == MM_PLAY || st == MM_OPTIONS || st == MM_QUIT) {
    draw_main_menu(st);
  }

  wrefresh(gamewin);
	wrefresh(debugwin);
}

void draw_game() {
  world.draw(gamewin, coords.x, coords.y, GW_CTRX, GW_CTRY, true);
  player.draw(gamewin, GW_CTRY - 2, GW_CTRX - 2, true);
}

void draw_main_menu(AppState selected) {
  int btn_width = 16;
  int top_btn_y = 10;

  selected == MM_PLAY && wattron(gamewin, COLOR_PAIR(Colors::btn_hghl.cp));
  draw_box(gamewin, top_btn_y,   GW_CTRC - btn_width/2 - 1, btn_width, 3);
  mvwaddstr(gamewin, top_btn_y+1, GW_CTRC - btn_width/2, "     Play     ");
  selected == MM_PLAY && wattroff(gamewin, COLOR_PAIR(Colors::btn_hghl.cp));

  selected == MM_OPTIONS && wattron(gamewin, COLOR_PAIR(Colors::btn_hghl.cp));
  draw_box(gamewin, top_btn_y+4, GW_CTRC - btn_width/2 - 1, btn_width, 3);
  mvwaddstr(gamewin, top_btn_y+5, GW_CTRC - btn_width/2, "    Options   ");
  selected == MM_OPTIONS && wattroff(gamewin, COLOR_PAIR(Colors::btn_hghl.cp));

  selected == MM_QUIT && wattron(gamewin, COLOR_PAIR(Colors::btn_hghl.cp));
  draw_box(gamewin, top_btn_y+8, GW_CTRC - btn_width/2 - 1, btn_width, 3);
  draw_box(gamewin, top_btn_y+8, GW_CTRC - btn_width/2 - 1, btn_width, 3);
  mvwaddstr(gamewin, top_btn_y+9, GW_CTRC - btn_width/2, "     Quit     ");
  selected == MM_QUIT && wattroff(gamewin, COLOR_PAIR(Colors::btn_hghl.cp));
}

void end() {
  curs_set(1);
  echo();
  nocbreak();
  endwin();
}
