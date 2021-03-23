#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ncurses.h>
#include <random>
#include <string>
#include <thread>

#include "chat.hpp"
#include "game.hpp"
#include "gfx_core.hpp"
#include "player.hpp"
#include "world.hpp"

#include "util/debug_print.hpp"
#include "util/keypress.hpp"
#include "util/misc.hpp"
#include "util/prelim.hpp"

#include "data/blocks.hpp"
#include "data/button.hpp"
#include "data/colors.hpp"
#include "data/constants.hpp"

#define ESC 27

#define US_PER_SEC 1000000
#define TARGET_FPS 30

AppState st = AppState::MAIN_MENU;
FocusType fc = FocusType::MENU;

int cur_btn = 0;

Coords coords;
Player player;
World  world;
Chat   chat;

WINDOW *gamewin, *debugwin, *achvwin, *chatwin;

chtype default_bkgd;

int GW_ROWS, GW_COLS, GW_CTRY, GW_CTRX, GW_CTRR, GW_CTRC;

std::random_device rand_dev;
std::mt19937 rng(rand_dev());

char logo_path[100];
char splash[50];

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
  world.plane.set_data(22, 24, Unit("><", 0));

  gamewin = newwin(26, 50, 5, 9);
  getmaxyx(gamewin, GW_ROWS, GW_COLS);
  fill_constants(GW_ROWS, GW_COLS, GW_CTRR, GW_CTRC, GW_CTRX, GW_CTRY);

  debugwin = newwin(4,  52, 0, 8);
  achvwin  = newwin(4,  30, 0, 61);
  chatwin  = newwin(26, 30, 5, 61);

  curses_init_win(gamewin);
  curses_init_win(debugwin);

  curses_init_pairs();

  default_bkgd = getbkgd(gamewin);
  wbkgdset(gamewin, COLOR_PAIR(Colors::win_brdr.cp));

  int logo_success = set_logo(logo_path, rng);
  if (logo_success != 0) return -3;

  int splash_success = set_splash(splash, rng);
  if (splash_success != 0) return -4;

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
  int ch = wgetch(gamewin);
  int result = handle_keypress(ch, st, fc);

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
    if (st == AppState::MAIN_MENU) {
      if (cur_btn == 0) {
        wbkgdset(gamewin, default_bkgd);
        st = AppState::GAME;
        fc = FocusType::GAME;
      }
      else if (cur_btn == 1) {
        cur_btn = 0;
        st = AppState::OPTIONS;
        fc = FocusType::MENU;
      }
      else if (cur_btn == 2) {
        return -1;
      }
    }
    else if (st == AppState::OPTIONS) {
      if (cur_btn == 10) {
        cur_btn = 0;
        st = AppState::MAIN_MENU;
        fc = FocusType::MENU;
      }
    }
  }
  else if (result == ActionChat::focus) {
    fc = FocusType::CHAT;
  }
  else if (result == ActionChat::cmd) {
    fc = FocusType::CHAT;
    chat.i_am_typing("/");
  }
  else if (result == ActionChat::send) {
    chat.i_am_typing("");
  }
  else if (result == ActionChat::unfcs) {
    fc = FocusType::GAME;
  }
  else if (result == ActionMisc::other) {
    if (fc == FocusType::CHAT) {
      chat.i_am_typing_more(std::string(1, (char) ch));
    }
  }
  else if (result == ActionMisc::idle) {
    return 0;
  }
  else {
    return -2;
  }

  return 0;
}

void output() {
	werase(gamewin);
	werase(debugwin);
  werase(achvwin);
  werase(chatwin);

	dwborder(debugwin);

  wattron(gamewin, COLOR_PAIR(Colors::win_brdr.cp));
	dwborder(gamewin);
  wattroff(gamewin, COLOR_PAIR(Colors::win_brdr.cp));

  dwborder(achvwin);
  dwborder(chatwin);

  coords.d_print(debugwin, 1, 3);
  d_print_maxwin(debugwin, 1, 32, gamewin);

  if (st == AppState::GAME) {
    draw_game();
    draw_chat();
  }
  else if (st == AppState::MAIN_MENU) {
    draw_main_menu(cur_btn);
    draw_info();
  }
  else if (st == AppState::OPTIONS) {
    draw_options(cur_btn);
  }

  wrefresh(gamewin);
	wrefresh(debugwin);
  wrefresh(achvwin);
  wrefresh(chatwin);
}

void draw_game() {
  world.draw(gamewin, coords.x, coords.y, GW_CTRX, GW_CTRY, true);
  player.draw(gamewin, GW_CTRY - 2, GW_CTRX - 2, true);
}

void draw_chat() {
  mvwaddstr(chatwin, 2, 2, "Test");
  chat.draw(chatwin);
}

void draw_main_menu(int cur_btn) {
  draw_txt(gamewin, 2, 4, logo_path, COLOR_PAIR(Colors::sect_hdr.cp) | A_BOLD);

  wattron(gamewin, COLOR_PAIR(Colors::splash.cp));
  mvwaddstr(gamewin, 6, GW_COLS - strlen(splash) - 3, splash);
  wattroff(gamewin, COLOR_PAIR(Colors::splash.cp));

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

void draw_info() {
  mvwaddstr(achvwin, 1, 1, "Welcome to Minhcraft!");
  mvwaddstr(achvwin, 2, 1, "See the starter guide below:");

  draw_txt(chatwin, 1, 1, CLC_APPDATA "intro.txt");
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
