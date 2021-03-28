#include <ncurses.h>
#include <vector>

#include "chat.hpp"
#include "command.hpp"

Chat::Chat() {
  /* default ctor does nothing */;
}

Chat::Chat(std::vector<Message> messages, WINDOW *chatwin) : cmd_env(chatwin) {
  this->messages = messages;
}

void Chat::add_message(Message message) {
  messages.push_back(message);
}

Message Chat::get_message(int recentness) {
  if (messages.size() == 0) {
    return "{% No messages here! %}";
  }
  else if (recentness == MSG_OLDEST) {
    return messages.at(0);
  }
  else if (recentness == MSG_NEWEST) {
    return messages.back();
  }
  else {
    return messages.at(recentness);
  }
}

void Chat::i_am_typing(Message message) {
  what_im_typing = message;
}

void Chat::i_am_typing_more(Message more) {
  what_im_typing.append(more);
}

void Chat::backspace() {
  if (what_im_typing.length() > 0) {
    what_im_typing.pop_back();
  }
}

void Chat::send() {
  if (what_im_typing.at(0) == '/') {
    std::string to_print;
    cmd_env.exec(what_im_typing.substr(1), to_print);
    add_message(to_print);
  }

  i_am_typing("");
}

void Chat::draw(WINDOW *win) {
  int rows, cols;
  getmaxyx(win, rows, cols);

  mvwaddstr(win, 5, 1, get_message(MSG_NEWEST).c_str());

  mvwaddch(win, rows - 3, 0,        ACS_LTEE);
  mvwaddch(win, rows - 3, cols - 1, ACS_RTEE);
  mvwhline(win, rows - 3, 1,        ACS_HLINE, cols - 2);

  mvwaddstr(win, rows - 2, 1, what_im_typing.c_str());
  waddstr(win, "_");
}
