#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ncurses.h>
#include <random>
#include <string>
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

std::random_device rand_dev;
std::mt19937 rng(rand_dev());

char logo_path[100];

int init() {
  int result = curses_init_seq();
  if (result != 0) {
    return result;
  }

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

  int logo_easter = get_rand_num(0, 4, rng);

  if (logo_easter == 0) {
    strcpy(logo_path, CLC_APPDATA "asciiart/logo.txt");
  }
  else if (logo_easter == 1) {
    strcpy(logo_path, CLC_APPDATA "asciiart/logo_alt_a.txt");
  }
  else if (logo_easter == 2) {
    strcpy(logo_path, CLC_APPDATA "asciiart/logo_alt_b.txt");
  }
  else if (logo_easter == 3) {
    strcpy(logo_path, CLC_APPDATA "asciiart/logo_alt_c.txt");
  }
  else {
    return -3; // Illegal random number
  }

  return 0;
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
  int result = handle_keypress(wgetch(gamewin));

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
    cur_btn = get_up_btn(cur_btn, st);
  }
  else if (result == ActionSelect::sel_down) {
    cur_btn = get_down_btn(cur_btn, st);
  }
  else if (result == ActionSelect::sel_left) {
    cur_btn = get_left_btn(cur_btn, st);
  }
  else if (result == ActionSelect::sel_right) {
    cur_btn = get_right_btn(cur_btn, st);
  }
  else if (result == ActionSelect::sel_ok) {
    if (st == MAIN_MENU) {
      if (cur_btn == 0) {
        wbkgdset(gamewin, default_bkgd);
        st = GAME;
      }
      else if (cur_btn == 1) {
        cur_btn = 0;
        st = OPTIONS;
      }
      else if (cur_btn == 2) {
        return -1;
      }
    }
    else if (st == OPTIONS) {
      if (cur_btn == 10) {
        cur_btn = 0;
        st = MAIN_MENU;
      }
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
  draw_txt(gamewin, 2, 4, logo_path, COLOR_PAIR(Colors::sect_hdr.cp) | A_BOLD);

  int btn_width = 16;
  int btn_height = 3;
  int top  = 10;
  int left = GW_CTRC - btn_width/2 - 1;

  for (int btn_no = 0; btn_no < 3; ++btn_no) {
    draw_btn(
      gamewin, top + (btn_height+1) * btn_no, left, btn_width, btn_height,
      1, 1, btn_labels[0][btn_no], cur_btn == btn_no
    );
  }
}

void draw_options(int cur_btn) {
  draw_txt(gamewin, 2, 13, CLC_APPDATA "asciiart/options.txt", COLOR_PAIR(Colors::sect_hdr.cp) | A_BOLD);

  int btn_width = 22;
  int btn_height = 3;
  int top  = 6;
  int left = GW_CTRC - btn_width - 1;

  for (int btn_no = 0; btn_no < 10; ++btn_no) {
    if (btn_no % 2 == 0) { // left column
      draw_btn(
        gamewin, top + btn_height * (btn_no / 2), left, btn_width, btn_height,
        1, 1, btn_labels[1][btn_no], cur_btn == btn_no
      );
    }
    else { // right column
      draw_btn(
        gamewin, top + btn_height * (btn_no / 2), GW_CTRC + 1, btn_width, btn_height,
        1, 1, btn_labels[1][btn_no], cur_btn == btn_no
      );
    }
  }

  draw_btn( // "back" button (at bottom)
    gamewin, top + btn_height * 5, GW_CTRC - btn_width/2 - 1, btn_width, btn_height,
    1, 1, btn_labels[1][10], cur_btn == 10
  );
}

void end() {
  curs_set(1);
  echo();
  nocbreak();
  endwin();
}
