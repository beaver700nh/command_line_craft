#include <stdexcept>

#include <ncurses.h>

#include "gfx_core.hpp"
#include "util/misc.hpp"

#include "world.hpp"

#include "data/blocks.hpp"
#include "data/colors.hpp"

/*************** World ***************/

World::World() {
  /* default ctor does nothing */;
}

World::World(int chunk_radius) {
  this->chunk_radius = chunk_radius;
  generate();
}

int World::load_chunk(int chunk_id) {
  return 0;
}

void World::draw(WINDOW *win, long x, long y, int at_x, int at_y, bool should_offset) {
  int rows, cols;
  getmaxyx(win, rows, cols);

  // for (int row = (should_offset ? rows - 3 : rows); row >= 0; --row) {
  //   for (int col = 0; col < (should_offset ? (cols - 2) / 2 : cols); ++col) {
  //     try {
  //       plane.get_data(col - at_x + x, row - at_y - y).draw(win, rows - 3 - row, col, should_offset);
  //     }
  //     catch (std::out_of_range &e) {
  //       Unit("`.", 0).draw(win, rows - 3 - row, col, should_offset);
  //     }
  //   }
  // }

  for (int row = 0; row < (should_offset ? rows - 2 : rows); ++row) {
    for (int col = 0; col < (should_offset ? (cols - 2) / 2 : cols); ++col) {
      try {
        // plane.get_data(col - at_x + x, row - at_y - y).draw(win, row, col, should_offset);
        plane.get_data(x - at_x + col, y + at_y - row).draw(win, row, col, should_offset);
      }
      catch (std::out_of_range &e) {
        Unit("`.", 0).draw(win, row, col, should_offset);
      }
    }
  }
}

void World::draw(WINDOW *win, Coords coords, int at_x, int at_y, bool should_offset) {
  draw(win, coords.x, coords.y, at_x, at_y, should_offset);
}

void World::generate() {
  plane = Plane<Unit>(Unit(Blocks::dirt.repr, Colors::dirt.cp, Colors::dirt.fg, Colors::dirt.bg), CHUNK_WIDTH * chunk_radius, 256);
}
