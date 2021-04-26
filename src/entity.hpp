#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <ncurses.h>
#include <vector>

#include "world.hpp"

#include "util/misc.hpp"

class Entity {
  public:
    Entity();
    Entity(World *world, Entity &entity);
    Entity(
      World *world, Coords coords, Coords hitbox, bool gravity,
      std::vector<std::vector<Unit>> texture
    );

    void tick();
    void draw(WINDOW *win);

    Coords coords;
    Coords hitbox;
    World *world;

    std::vector<std::vector<Unit>> texture;

    bool gravity = true;
};

#endif
