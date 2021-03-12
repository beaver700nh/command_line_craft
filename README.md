# Command-Linecraft
### A Minecraft Clone in the Terminal
This program uses ncurses to draw graphics in the terminal.

# The game

## How to play:
TODO

## Data packs (Block data, Recipes, Etc.)
In the src/data/ directory, TODO

# Compilation

## Main source code
The src/ directory

## Util functions used by the source code
Look in src/util/

## To compile the game
run `build/compile.sh` then type:

* `c <RET>` or `<RET>` to compile the game (case INsensitive)
* `e <RET>` to run the game
* `E <RET>` to compile and run the game
* `o <RET>` to run the color test
* `O <RET>` to compile and run the color test

These are all case SENSITIVE except for the first one (`C`).
You can also pass the action as a command line argument. For example,

`build/compile.sh E`

compiles and runs the game.

# NOTE: If the terminal displays gibberish
Try typing this at the command prompt:
`$ reset`
