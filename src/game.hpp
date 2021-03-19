#ifndef GAME_HPP
#define GAME_HPP

typedef enum {MAIN_MENU, GAME, OPTIONS} AppState;

void init();

int tick();

int input();
void output();

void draw_game();
void draw_main_menu(int cur_btn);
void draw_options(int cur_btn);

void end();

int handle_keypress(int ch);

#endif
