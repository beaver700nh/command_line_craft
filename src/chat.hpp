#ifndef CHAT_HPP
#define CHAT_HPP

#include <ncurses.h>
#include <string>
#include <vector>

#include "command.hpp"

typedef std::string Message;

#define MSG_OLDEST -1
#define MSG_NEWEST -2

class Chat {
  public:
    Chat();
    Chat(std::vector<Message> messages, WINDOW *chatwin);

    void add_message(Message message);
    Message get_message(int recentness);

    void i_am_typing(Message message);
    void i_am_typing_more(Message more);

    void backspace();

    void send();

    void draw(WINDOW *win);

  private:
    std::vector<Message> messages;
    Message what_im_typing;

    CmdEnv cmd_env;
};

#endif
