#include <ncurses.h>

#include "gfx_core.hpp"
#include "util/misc.hpp"

#include "world.hpp"

#include "data/blocks.hpp"

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

void World::draw(WINDOW *win, long x, long y) {
  int rows, cols;
  getmaxyx(win, rows, cols);

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      plane.get_data(x + col, y + row).draw(win, row, col);
    }
  }
}

void World::draw(WINDOW *win, Coords coords) {
  draw(win, coords.x, coords.y);
}

void World::generate() {
  plane = Plane<Unit>(Unit(Blocks::Dirt::repr(), 0), CHUNK_WIDTH * chunk_radius, 256);
}
