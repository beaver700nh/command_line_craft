#include <algorithm>
#include <iterator>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "command.hpp"

CmdEnv::CmdEnv() {
  /* default ctor does nothing */;
}

CmdEnv::CmdEnv(WINDOW *chatwin) {
  this->chatwin = chatwin;
}

int CmdEnv::exec(std::string cmd, std::string &to_print) {
  std::istringstream iss(cmd);
  std::vector<std::string> tokens {
    std::istream_iterator<std::string>{iss},
    std::istream_iterator<std::string>{}
  };

  // for (int i = 0; i < tokens.size(); ++i) {
  //   mvwaddstr(chatwin, i+1, 1, tokens.at(i).c_str());
  // }
  to_print = cmd;

  return 0;
}
