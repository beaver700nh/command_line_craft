function execute() {
  echo -e "\x1b[32m================ Executing (Main Program) ... ================\x1b[0m"
  sleep 2
  ./build/main
}

function execute_color_test() {
  echo -e "\x1b[32m================ Executing (Color Test) ... ================\x1b[0m"
  sleep 2
  ./build/colortest
}

read -p "Action? [c/e/o] " action

if [[ "$action" == "C" || "$action" == "c" || "$action" == "" ]]; then
  echo -e "\x1b[32m================ Compiling (Main Program) ... ================\x1b[0m"

  if clang++-7 -pthread -std=c++17 -o build/main -lncurses src/*.cpp src/*/*.cpp --verbose; then
    echo -e "\x1b[1;34mSuccess! (Main Program)\x1b[0m"

  else
    echo -e "\x1b[31mFailed! (Main Program)\x1b[0m"

  fi

elif [[ "$action" == "E" ]]; then
  echo -e "\x1b[32m================ Compiling (Main Program) ... ================\x1b[0m"

  if clang++-7 -pthread -std=c++17 -o build/main -lncurses src/*.cpp src/*/*.cpp --verbose; then
    execute

  else
    echo -e "\x1b[31mFailed! (Main Program)\x1b[0m"

  fi

elif [[ "$action" == "e" ]]; then
  execute

elif [[ "$action" == "O" ]]; then
  echo -e "\x1b[32m================ Compiling (Color Test) ... ================\x1b[0m"

  if clang++-7 -pthread -std=c++17 -o build/colortest -lncurses tests/colortest.cpp --verbose; then
    execute_color_test

  fi

elif [[ "$action" == "o" ]]; then
  execute_color_test

else
  echo -e "\x1b[31mNo such action: $action\x1b[0m"

fi
