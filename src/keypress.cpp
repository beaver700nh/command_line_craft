#include <ncurses.h>

#include "event.hpp"
#include "game.hpp"
#include "keypress.hpp"

Event handle_keypress(int ch, AppState st, FocusType fc) {
  if (ch == ERR) {
    return Event(EventType::MISC, "idle");
  }
  else if (ch == 27) {
    if (fc == FocusType::MENU && st == AppState::MAIN_MENU) {
      return Event(EventType::MISC, "quit");
    }
    else if (fc == FocusType::GAME) {
      return Event(EventType::MISC, "qtmm");
    }
    else if (fc == FocusType::CHAT) {
      return Event(EventType::CHAT, "unfocus");
    }
  }
  else if (fc == FocusType::CHAT) {
    if (ch == '\n' || ch == '\r') {
      return Event(EventType::CHAT, "send");
    }
    else if (ch == '\b' || ch == 127 || ch == KEY_BACKSPACE || ch == KEY_DC) {
      return Event(EventType::CHAT, "backspace");
    }
    else {
      return Event(EventType::CHAT, "typing");
    }
  }
  else if (ch == 'w') {
    if (fc == FocusType::GAME) {
      return Event(EventType::MOVE, "up");
    }
  }
  else if (ch == 'a') {
    if (fc == FocusType::GAME) {
      return Event(EventType::MOVE, "left");
    }
  }
  else if (ch == 's') {
    if (fc == FocusType::GAME) {
      return Event(EventType::MOVE, "down");
    }
  }
  else if (ch == 'd') {
    if (fc == FocusType::GAME) {
      return Event(EventType::MOVE, "right");
    }
  }
  else if (ch == 'e') {
    if (fc == FocusType::GAME) {
      return Event(EventType::INTERACT, "bed");
    }
  }
  else if (ch == KEY_UP) {
    if (fc == FocusType::MENU) {
      return Event(EventType::SELECT, "up");
    }
  }
  else if (ch == KEY_DOWN) {
    if (fc == FocusType::MENU) {
      return Event(EventType::SELECT, "down");
    }
  }
  else if (ch == KEY_LEFT) {
    if (fc == FocusType::MENU) {
      return Event(EventType::SELECT, "left");
    }
  }
  else if (ch == KEY_RIGHT) {
    if (fc == FocusType::MENU) {
      return Event(EventType::SELECT, "right");
    }
  }
  else if (ch == '\n' || ch == '\r') {
    if (fc == FocusType::MENU) {
      return Event(EventType::SELECT, "confirm");
    }
  }
  else if (ch == 't') {
    if (fc == FocusType::GAME) {
      return Event(EventType::CHAT, "focus");
    }
  }
  else if (ch == '/') {
    if (fc == FocusType::GAME) {
      return Event(EventType::CHAT, "command");
    }
  }

  return Event(EventType::MISC, "other");
}
