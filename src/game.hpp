#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>

typedef enum {MAIN_MENU, GAME, OPTIONS} AppState;

int init();

int tick();

int input();
void output();

void draw_game();
void draw_main_menu(int cur_btn);
void draw_options(int cur_btn);
void draw_txt(WINDOW *win, int row, int col, const char *fname, int style = 0);

void end();

int handle_keypress(int ch);

#endif
