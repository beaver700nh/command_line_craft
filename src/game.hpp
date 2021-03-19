#ifndef GAME_HPP
#define GAME_HPP

//#define fill_constants(rows, cols, ctrr, ctrc, ctrx, ctry) (ctrr = rows/2, ctrc = cols/2, ctry = ctrr, ctrx = ctrc/2);

typedef enum {MAIN_MENU, MM_PLAY, MM_OPTIONS, MM_QUIT, GAME} AppState;

void init();

int tick();

int input();
void output();

void draw_game();
void draw_main_menu(int hghl_btn);

void end();

int handle_keypress(int ch);

#endif
