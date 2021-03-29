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
#include "gui.hpp"
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

#define US_PER_SEC 1000000
#define TARGET_FPS 30

AppState st = AppState::MAIN_MENU;
FocusType fc = FocusType::MENU;

MenuScreen main_ms, opts_ms;

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

  if (set_logo(logo_path, rng) != 0) return -3;
  if (set_splash(splash, rng) != 0) return -4;

  gamewin = newwin(26, 50, 5, 9);
  getmaxyx(gamewin, GW_ROWS, GW_COLS);
  fill_constants(GW_ROWS, GW_COLS, GW_CTRR, GW_CTRC, GW_CTRX, GW_CTRY);

  debugwin = newwin(4,  52, 0, 8);
  achvwin  = newwin(4,  30, 0, 61);
  chatwin  = newwin(26, 30, 5, 61);

  curses_init_win(gamewin);
  curses_init_win(debugwin);
  curses_init_win(achvwin);
  curses_init_win(chatwin);
  curses_init_pairs();

  default_bkgd = getbkgd(gamewin);
  wbkgdset(gamewin, COLOR_PAIR(Colors::win_brdr.cp));

  player = Player(
    Unit(PlayerReprs::up1(), 0), Unit(PlayerReprs::up2(), 0), \
    Unit(PlayerReprs::dn1(), 0), Unit(PlayerReprs::dn2(), 0)
  );

  world = World(3);
  world.plane.set_data(22, 24, Unit("><", 0));

  world.plane.set_data( 3,  3, Unit("UR", 0));
  world.plane.set_data(-3,  3, Unit("UL", 0));
  world.plane.set_data( 3, -3, Unit("LR", 0));
  world.plane.set_data(-3, -3, Unit("LL", 0));
  
  main_ms = MenuScreen(
    MenuHeader(2, 4, logo_path, MHType::FILE, COLOR_PAIR(Colors::sect_hdr.cp) | A_BOLD),
    {
      MenuButton(10, GW_CTRC - 9, 16, 3, "Play",    0, true),
      MenuButton(14, GW_CTRC - 9, 16, 3, "Options", 1, true),
      MenuButton(18, GW_CTRC - 9, 16, 3, "Quit",    2, true),
    },
    {
      {{UP, 2}, {DOWN, 1}, {LEFT, 0}, {RIGHT, 0}},
      {{UP, 0}, {DOWN, 2}, {LEFT, 1}, {RIGHT, 1}},
      {{UP, 1}, {DOWN, 0}, {LEFT, 2}, {RIGHT, 2}},
    }
  );

  opts_ms = MenuScreen(
    MenuHeader(2, 13, CLC_APPDATA "asciiart/options.txt", MHType::FILE, COLOR_PAIR(Colors::sect_hdr.cp) | A_BOLD),
    {
      MenuButton(6,  GW_CTRC - 23, 22, 3, "Music: xx%",         0,  true),
      MenuButton(6,  GW_CTRC + 1,  22, 3, "Sound Effects: xx%", 1,  true),
      MenuButton(9,  GW_CTRC - 23, 22, 3, "Invert Mouse: xxx",  2,  true),
      MenuButton(9,  GW_CTRC + 1,  22, 3, "Difficulty: xxxxxx", 3,  true),
      MenuButton(12, GW_CTRC - 23, 22, 3, "TBD, IDK yet",       4,  true),
      MenuButton(12, GW_CTRC + 1,  22, 3, "Controls...",        5,  true),
      MenuButton(15, GW_CTRC - 23, 22, 3, "Texture Packs...",   6,  true),
      MenuButton(15, GW_CTRC + 1,  22, 3, "Recipes...",         7,  true),
      MenuButton(18, GW_CTRC - 23, 22, 3, "Color Packs...",     8,  true),
      MenuButton(18, GW_CTRC + 1,  22, 3, "Items...",           9,  true),
      MenuButton(21, GW_CTRC - 12, 22, 3, "Back to Main Menu",  10, true),
    },
    {
      {{UP, 10}, {DOWN,  2}, {LEFT,  1}, {RIGHT,  1}},
      {{UP, 10}, {DOWN,  3}, {LEFT,  0}, {RIGHT,  0}},
      {{UP,  0}, {DOWN,  4}, {LEFT,  3}, {RIGHT,  3}},
      {{UP,  1}, {DOWN,  5}, {LEFT,  2}, {RIGHT,  2}},
      {{UP,  2}, {DOWN,  6}, {LEFT,  5}, {RIGHT,  5}},
      {{UP,  3}, {DOWN,  7}, {LEFT,  4}, {RIGHT,  4}},
      {{UP,  4}, {DOWN,  8}, {LEFT,  7}, {RIGHT,  7}},
      {{UP,  5}, {DOWN,  9}, {LEFT,  6}, {RIGHT,  6}},
      {{UP,  6}, {DOWN, 10}, {LEFT,  9}, {RIGHT,  9}},
      {{UP,  7}, {DOWN, 10}, {LEFT,  8}, {RIGHT,  8}},
      {{UP,  8}, {DOWN,  0}, {LEFT, 10}, {RIGHT, 10}},
    }
  );

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
  else if (result == ActionMisc::qtmm) {
    wbkgdset(gamewin, COLOR_PAIR(Colors::win_brdr.cp));
    main_ms.highlight(0);
    st = AppState::MAIN_MENU;
    fc = FocusType::MENU;
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
    if (st == AppState::MAIN_MENU) {
      main_ms.highlight(main_ms.go(UP));
    }
    else if (st == AppState::OPTIONS) {
      opts_ms.highlight(opts_ms.go(UP));
    }
  }
  else if (result == ActionSelect::sel_down) {
    if (st == AppState::MAIN_MENU) {
      main_ms.highlight(main_ms.go(DOWN));
    }
    else if (st == AppState::OPTIONS) {
      opts_ms.highlight(opts_ms.go(DOWN));
    }
  }
  else if (result == ActionSelect::sel_left) {
    if (st == AppState::MAIN_MENU) {
      main_ms.highlight(main_ms.go(LEFT));
    }
    else if (st == AppState::OPTIONS) {
      opts_ms.highlight(opts_ms.go(LEFT));
    }
  }
  else if (result == ActionSelect::sel_right) {
    if (st == AppState::MAIN_MENU) {
      main_ms.highlight(main_ms.go(RIGHT));
    }
    else if (st == AppState::OPTIONS) {
      opts_ms.highlight(opts_ms.go(RIGHT));
    }
  }
  else if (result == ActionSelect::sel_ok) {
    if (st == AppState::MAIN_MENU) {
      if (main_ms.highlighting(0)) {
        wbkgdset(gamewin, default_bkgd);
        st = AppState::GAME;
        fc = FocusType::GAME;
      }
      else if (main_ms.highlighting(1)) {
        main_ms.highlight(0);
        opts_ms.highlight(0);
        st = AppState::OPTIONS;
        fc = FocusType::MENU;
      }
      else if (main_ms.highlighting(2)) {
        return -1;
      }
    }
    else if (st == AppState::OPTIONS) {
      if (opts_ms.highlighting(10)) {
        opts_ms.highlight(0);
        main_ms.highlight(0);
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
    chat.send();
  }
  else if (result == ActionChat::unfcs) {
    fc = FocusType::GAME;
  }
  else if (result == ActionChat::bksp) {
    chat.backspace();
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
    main_ms.draw(gamewin, 0, 0);
    wattron(gamewin, COLOR_PAIR(Colors::splash.cp));
    mvwaddstr(gamewin, 6, GW_COLS - 3 - strlen(splash), splash);
    wattroff(gamewin, COLOR_PAIR(Colors::splash.cp));
    draw_info();
  }
  else if (st == AppState::OPTIONS) {
    opts_ms.draw(gamewin, 0, 0);
  }

  wrefresh(gamewin);
	wrefresh(debugwin);
  wrefresh(achvwin);
  wrefresh(chatwin);
}

void draw_game() {
  world.draw(gamewin, coords, GW_CTRX - 1, GW_CTRY - 1, true);
  player.draw(gamewin, GW_CTRY - 1, GW_CTRX - 1, true);
}

void draw_chat() {
  mvwaddstr(chatwin, 2, 2, "Test");
  chat.draw(chatwin);
}

void draw_info() {
  mvwaddstr(achvwin, 1, 1, "Welcome to Minhcraft!");
  mvwaddstr(achvwin, 2, 1, "See the starter guide below:");

  draw_txt(chatwin, 1, 1, CLC_APPDATA "intro.txt");
}

void end() {
  curs_set(1);
  echo();
  nocbreak();
  endwin();
}
