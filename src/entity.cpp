#include <ncurses.h>
#include <vector>

#include "entity.hpp"
#include "world.hpp"

#include "util/misc.hpp"

Entity::Entity() {
  /* default ctor does nothing */;
}

Entity::Entity(World *world, Entity &entity) : world(world) {
  coords = entity.coords;
}

Entity::Entity(
  World *world, Coords coords, Coords hitbox, bool gravity,
  std::vector<std::vector<Unit>> texture
) : world(world) {
  this->coords = coords;
  this->hitbox = hitbox;
  this->gravity = gravity;
  this->texture = texture;
}

void Entity::tick() {
  /* does nothing; to be overridden by children */;
}

void Entity::draw(WINDOW *win) {
  for (int row = 0; row < hitbox.y; ++row) {
    for (int col = 0; col < hitbox.x; ++col) {
      if (texture[row][col].is_wide) {
        s_mvwaddch(
          win, coords.y - row, coords.x + col,
          texture[row][col].wrepr[0]
        );
        s_mvwaddch(
          win, coords.y - row, coords.x + col,
          texture[row][col].wrepr[1]
        );
      }
      else {
        s_mvwaddstr(
          win, coords.y - row, coords.x + col,
          texture[row][col].nrepr
        );
      }
    }
  }
}
