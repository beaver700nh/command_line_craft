#ifndef SCALE_MACROS_HPP
#define SCALE_MACROS_HPP

#include <ncurses.h>

#define s_mvaddch(row, col, ch)             mvaddch((row), (col)*2, (ch))
#define s_mvaddstr(row, col, str)           mvaddstr((row), (col)*2, (str))
#define s_mvaddnstr(row, col, str, n)       mvaddnstr((row), (col)*2, (str), (n))

#define s_mvwaddch(win, row, col, ch)       mvwaddch((win), (row), (col)*2, (ch))
#define s_mvwaddstr(win, row, col, str)     mvwaddstr((win), (row), (col)*2, (str))
#define s_mvwaddnstr(win, row, col, str, n) mvwaddnstr((win), (row), (col)*2, (str), (n))

#define s_mvaddwch(row, col, ch)               mvaddwch((row), (col)*2, (ch))
#define s_mvaddwchstr(row, col, str)           mvaddwchstr((row), (col)*2, (str))
#define s_mvaddwchnstr(row, col, str, n)       mvaddwchnstr((row), (col)*2, (str), (n))

#define s_mvwaddwch(win, row, col, ch)         mvwaddwch((win), (row), (col)*2, (ch))
#define s_mvwaddwchstr(win, row, col, str)     mvwaddwchstr((win), (row), (col)*2, (str))
#define s_mvwaddwchnstr(win, row, col, str, n) mvwaddwchnstr((win), (row), (col)*2, (str), (n))

#endif
