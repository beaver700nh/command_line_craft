#include <string>

#include "event.hpp"

Event::Event() {
  /* default ctor does nothing */;
}

Event::Event(EventType type, std::string desc) {
  this->type = type;
  this->desc = desc;
}
