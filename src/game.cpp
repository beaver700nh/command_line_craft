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
#include "util/misc.hpp"

#include "data/blocks.hpp"
#include "data/colors.hpp"
#include "data/button.hpp"

#define ESC 27

#define US_PER_SEC 1000000
#define TARGET_FPS 30

AppState st = MAIN_MENU;
int cur_btn = 0;

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
  fill_constants(GW_ROWS, GW_COLS, GW_CTRR, GW_CTRC, GW_CTRX, GW_CTRY);

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
    cur_btn = get_prev_btn(cur_btn, st);
  }
  else if (result == ActionSelect::sel_down) {
    cur_btn = get_next_btn(cur_btn, st);
  }
  else if (result == ActionSelect::sel_ok) {
    if (cur_btn == 0) {
      wbkgdset(gamewin, default_bkgd);
      st = GAME;
    }
    else if (cur_btn == 1) {
      st = OPTIONS;
    }
    else if (cur_btn == 2) {
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
  else if (st == MAIN_MENU) {
    draw_main_menu(cur_btn);
  }
  else if (st == OPTIONS) {
    cur_btn = 1;
    draw_options(cur_btn);
  }

  wrefresh(gamewin);
	wrefresh(debugwin);
}

void draw_game() {
  world.draw(gamewin, coords.x, coords.y, GW_CTRX, GW_CTRY, true);
  player.draw(gamewin, GW_CTRY - 2, GW_CTRX - 2, true);
}

void draw_main_menu(int cur_btn) {
  int btn_width = 16;
  int btn_height = 3;
  int top_btn_y = 10;
  int all_btn_x = GW_CTRC - btn_width/2 - 1;

  draw_btn(gamewin, top_btn_y,   all_btn_x, btn_width, btn_height, 1, 1, btn_labels[0][0], cur_btn == 0);
  draw_btn(gamewin, top_btn_y+4, all_btn_x, btn_width, btn_height, 1, 1, btn_labels[0][1], cur_btn == 1);
  draw_btn(gamewin, top_btn_y+8, all_btn_x, btn_width, btn_height, 1, 1, btn_labels[0][2], cur_btn == 2);
}

void draw_options(int cur_btn) {
  /*
   * +--------------------+--------------------+
   * |     Music: xx%     | Sound Effects: xx% |
   * +--------------------+--------------------+
   * |  Invert Mouse: xxx | Difficulty: xxxxxx |
   * +--------------------+--------------------+
   * |         TBD        |     Controls...    |
   * +--------------------+--------------------+
   * |   Texture Packs... |     Recipes...     |
   * +--------------------+--------------------+
   * |    Color Packs...  |      Items...      |
   * +--------------------+--------------------+
   *
   */

  int btn_width = 20;
  int btn_height = 3;
  int top_btn_y = 10;
  int all_btn_x = GW_CTRC - btn_width/2 - 1;

  draw_btn(gamewin, top_btn_y,   all_btn_x, btn_width, btn_height, 1, 1, btn_labels[1][0], cur_btn == 0);
  draw_btn(gamewin, top_btn_y+4, all_btn_x, btn_width, btn_height, 1, 1, btn_labels[1][1], cur_btn == 1);
  draw_btn(gamewin, top_btn_y+8, all_btn_x, btn_width, btn_height, 1, 1, btn_labels[1][2], cur_btn == 2);
}

void end() {
  curs_set(1);
  echo();
  nocbreak();
  endwin();
}
