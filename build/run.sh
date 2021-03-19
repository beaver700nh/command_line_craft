#!/bin/bash

ACTION_OPT=$1
VERBOSE_OPT=$2

if [ $# -lt 1 ]; then
  read -p "Action? [c/e/o] " ACTION_OPT

fi

function execute() {
  echo -e "\x1b[32m================ Executing (Main Program) ... ================\x1b[0m"
  sleep 1
  ./build/main
}

function execute_color_test() {
  echo -e "\x1b[32m================ Executing (Color Test) ... ================\x1b[0m"
  sleep 1
  ./build/colortest
}

function compile() {
  clang++-7 -pthread -std=c++17 -o build/main -lncurses src/*.cpp src/*/*.cpp $1
  result=$?
}

function compile_color_test() {
  clang++-7 -pthread -std=c++17 -o build/colortest -lncurses tests/colortest.cpp $1
  result=$?
}

if [[ "$ACTION_OPT" == "C" || "$ACTION_OPT" == "c" || "$ACTION_OPT" == "" ]]; then
  echo -e "\x1b[32m================ Compiling (Main Program) ... ================\x1b[0m"

  compile $VERBOSE_OPT

  if [ "$result" -eq 0 ]; then
    echo -e "\x1b[1;34mSuccess! (Main Program)\x1b[0m"

  else
    echo -e "\x1b[31mFailed! (Main Program)\x1b[0m"

  fi

elif [[ "$ACTION_OPT" == "E" ]]; then
  echo -e "\x1b[32m================ Compiling (Main Program) ... ================\x1b[0m"

  compile $VERBOSE_OPT

  if [ "$result" -eq 0 ]; then
    execute

  else
    echo -e "\x1b[31mFailed! (Main Program)\x1b[0m"

  fi

elif [[ "$ACTION_OPT" == "e" ]]; then
  execute

elif [[ "$ACTION_OPT" == "O" ]]; then
  echo -e "\x1b[32m================ Compiling (Color Test) ... ================\x1b[0m"

  compile_color_test $VERBOSE_OPT

  if [ "$result" -eq 0 ]; then
    execute_color_test

  fi

elif [[ "$ACTION_OPT" == "o" ]]; then
  execute_color_test

else
  echo -e "\x1b[31mNo such action: $ACTION_OPT\x1b[0m"

fi
