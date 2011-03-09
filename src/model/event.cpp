/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <model/event.h>
using namespace model;

Event::Event() : type(NONE), description("") {} 
Event::Event(const EventType t, const char* desc) : type(t), description(desc) {}

Event::Event(const Event& e) : type(e.getType()), description(e.getDescription()) {}

Event::~Event() {}

EventType 
Event::getType() const {
    return type;
}

std::string
Event::getDescription() const {
    return description;
}
