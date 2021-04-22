#include "entity.hpp"
#include "world.hpp"

#include "util/misc.hpp"

Entity::Entity() {
  /* default ctor does nothing */;
}

Entity::Entity(const World &world, Entity &entity) : world(world) {
  coords = entity.coords;
}

Entity::Entity(const World &world, Coords coords) : world(world) {
  this->coords = coords;
}

Entity::Entity(const World &world, long x, long y) : world(world) {
  coords = Coords(x, y);
}
