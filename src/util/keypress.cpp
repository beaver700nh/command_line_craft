#include <ncurses.h>

#include "../game.hpp"

#include "keypress.hpp"

int handle_keypress(int ch, AppState st, FocusType fc) {
  if (ch == ERR) {
    return ActionMisc::idle;
  }
  else if (ch == 27) {
    if (fc == FocusType::MENU && st == AppState::MAIN_MENU) {
      return ActionMisc::quit;
    }
    else if (fc == FocusType::GAME) {
      return ActionMisc::qtmm;
    }
    else if (fc == FocusType::CHAT) {
      return ActionChat::unfcs;
    }
  }
  else if (ch == 'w') {
    if (fc == FocusType::GAME) {
      return ActionMove::up;
    }
  }
  else if (ch == 'a') {
    if (fc == FocusType::GAME) {
      return ActionMove::left;
    }
  }
  else if (ch == 's') {
    if (fc == FocusType::GAME) {
      return ActionMove::down;
    }
  }
  else if (ch == 'd') {
    if (fc == FocusType::GAME) {
      return ActionMove::right;
    }
  }
  else if (ch == 'e') { // TEMPORARY
    if (fc == FocusType::GAME) {
      return ActionInteract::sleep;
    }
  }
  else if (ch == KEY_UP) { // TEMPORARY
    return ActionSelect::sel_up;
  }
  else if (ch == KEY_DOWN) { // TEMPORARY
    return ActionSelect::sel_down;
  }
  else if (ch == KEY_LEFT) { // TEMPORARY
    return ActionSelect::sel_left;
  }
  else if (ch == KEY_RIGHT) { // TEMPORARY
    return ActionSelect::sel_right;
  }
  else if (ch == '\n' || ch == '\r') {
    if (fc == FocusType::MENU) {
      return ActionSelect::sel_ok;
    }
    else if (fc == FocusType::CHAT) {
      return ActionChat::send;
    }
  }
  else if (ch == '\b' || ch == 127 || ch == KEY_BACKSPACE || ch == KEY_DC) {
    if (fc == FocusType::CHAT) {
      return ActionChat::bksp;
    }
  }
  else if (ch == 't') {
    if (fc == FocusType::GAME) {
      return ActionChat::focus;
    }
  }
  else if (ch == '/') {
    if (fc == FocusType::GAME) {
      return ActionChat::cmd;
    }
  }

  return ActionMisc::other;
}
