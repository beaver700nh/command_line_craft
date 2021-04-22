#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "util/misc.hpp"

class Entity {
  public:
    Entity();
    Entity(const World &world, Entity &entity);
    Entity(const World &world, Coords coords);
    Entity(const World &world, long x, long y);

    Coords coords;
    World &world;
};

#endif
