#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <ncurses.h>

#include "util/misc.hpp"
#include "gfx_core.hpp"
#include "plane.hpp"

#define CHUNK_WIDTH 64

class World {
  public:
    World();
    World(int chunk_radius);

    void generate();

    int load_chunk(int chunk_id);

    void draw(WINDOW *win, long x, long y, bool has_border = false);
    void draw(WINDOW *win, Coords coords, bool has_border = false);

    static constexpr int ERR_COORDS_OOB = -1;

    Plane<Unit> plane;

  private:
    int chunk_radius;
    int current_chunk = 0;
};

#endif
