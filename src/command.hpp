#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>

class CmdEnv {
  public:
    CmdEnv();
    CmdEnv(WINDOW *chatwin);

    int exec(std::string cmd, std::string &to_print);

  private:
    std::unordered_map<std::string, int> effects;

    WINDOW *chatwin;
};

#endif
