#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../game.hpp"

extern const char btn_labels[][50][15];

int get_prev_btn(int cur_btn, AppState st);
int get_next_btn(int cur_btn, AppState st);

void draw_box(WINDOW *win, int row, int col, int width, int height);
void draw_btn(WINDOW *win, int row, int col, int width, int height, int text_row, int text_col, const char *text, bool hghl);

#endif
