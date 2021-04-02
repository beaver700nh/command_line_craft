#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "util/misc.hpp"

class Entity {
  public:
    Entity();
    Entity(Entity &entity);
    Entity(Coords coords);
    Entity(long x, long y);

    Coords coords;
};

#endif
