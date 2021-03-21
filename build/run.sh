#!/bin/bash

ACTION_OPT=$1
VERBOSE_OPT=$2

if [ $# -lt 1 ]; then
  read -p "Action? [c/e/t] " ACTION_OPT

fi

function execute() {
  echo -e "\x1b[32m================ Executing (Main Program) ... ================\x1b[0m"
  sleep 1
  ./build/main
}

function execute_test() {
  echo -e "\x1b[32m================ Executing (Test) ... ================\x1b[0m"
  sleep 1
  ./build/test
}

function compile() {
  clang++-7 -pthread -std=c++17 -o build/main -lncurses src/*.cpp src/*/*.cpp $1
  result=$?
}

function compile_test() {
  clang++-7 -pthread -std=c++17 -o build/test -lncurses $2 $1
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

elif [[ "$ACTION_OPT" == "T" ]]; then
  read -p "Which test? " the_test
  read -p "What links? " the_links

  echo -e "\x1b[32m================ Compiling ($the_test) ... ================\x1b[0m"

  compile_test $VERBOSE_OPT "tests/$the_test" $the_links

  if [ "$result" -eq 0 ]; then
    execute_test

  else
    echo -e "\x1b[31mFailed! (Test)\x1b[0m"

  fi

elif [[ "$ACTION_OPT" == "t" ]]; then
  execute_test

else
  echo -e "\x1b[31mNo such action: $ACTION_OPT\x1b[0m"

fi
