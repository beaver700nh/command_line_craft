#include "entity.hpp"

#include "util/misc.hpp"

Entity::Entity() {
  /* default ctor does nothing */;
}

Entity::Entity(Entity &entity) {
  coords = entity.coords;
}

Entity::Entity(Coords coords) {
  this->coords = coords;
}

Entity::Entity(long x, long y) {
  coords = Coords(x, y);
}
