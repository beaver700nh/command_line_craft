function execute() {
  echo -e "\x1b[32m================ Executing... ================\x1b[0m"
  sleep 2
  ./build/main
}

read -p "Action? [C/e] " action

if [[ "$action" == "C" || "$action" == "c" || "$action" == "" ]]; then
  echo -e "\x1b[32m================ Compiling... ================\x1b[0m"

  if clang++-7 -pthread -std=c++17 -o build/main -lncurses src/*.cpp src/*/*.cpp --verbose; then
    execute

  else
    echo -e "\x1b[31mFailed!\x1b[0m"

  fi

elif [[ "$action" == "e" ]]; then
  execute

else
  echo -e "\x1b[31mNo such action: $action\x1b[0m"

fi
