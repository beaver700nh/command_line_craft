#ifndef GAME_HPP
#define GAME_HPP

typedef enum {MM_PLAY, MM_OPTIONS, MM_QUIT, GAME} AppState;

void init();

int tick();

int input();
void output();

void draw_game();
void draw_main_menu(AppState selected);

void end();

int handle_keypress(int ch);

#endif
