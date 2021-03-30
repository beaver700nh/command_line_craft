#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

enum class EventType {MOVE, INTERACT, SELECT, CHAT, MISC};

class Event {
  public:
    Event();
    Event(EventType type, std::string desc);

    EventType type;
    std::string desc;
};

#endif
