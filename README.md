# Command-Linecraft
### A Minecraft Clone in the Terminal
This program uses ncurses to draw graphics in the terminal.

# The game

## Default controls (not fully implemented yet)

| Key     | Description                                                              |
| ------- | ------------------------------------------------------------------------ |
| WASD    | Move the character around                                                |
| Shift   | Toggles sprint mode (does not crouch)                                    |
| E       | Interact with a bed, lever, button, door, or trapdoor                    |
| F       | Eat the held item                                                        |
| Q       | Drop the held item                                                       |
| Space   | When in main game: jump                                                  |
| Space   | When in inventory: Change splitting (take one, drop one, or split stack) |

## Mouse key bindings
Since the terminal doesn't have a mouse, these key bindings replace the mouse:

| Key     | Description                                                            |
| ------- | ---------------------------------------------------------------------- |
| Enter   | Left click                                                             |
| Arrows  | Move mouse/cursor around                                               |
| Alt     | Toggle scroll mode                                                     |
| Ctrl    | Toggle drag mode                                                       |
| Shift   | IDK yet                                                                |

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
* `t <RET>` to run a test
* `T <RET>` to compile and run a test

These are all case SENSITIVE except for the first one (`C`).
You can also pass the action as a command line argument. For example,

```console
build/compile.sh E
```

compiles and runs the game.

# NOTE: If the terminal displays gibberish
Try typing this at the command prompt:
```console
$ reset
```
or this:
```console
$ echo -e "\x1b(B"
```
