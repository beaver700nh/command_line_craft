#include "keypress.hpp"

int handle_keypress(int ch) {
  if (ch == 27) {
    return ActionMisc::quit;
  }
  else if (ch == 'w') {
    return ActionMove::up;
  }
  else if (ch == 'a') {
    return ActionMove::left;
  }
  else if (ch == 's') {
    return ActionMove::down;
  }
  else if (ch == 'd') {
    return ActionMove::right;
  }
  else {
    return ActionMisc::other;
  }
}
