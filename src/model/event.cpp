/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "event.h"
using model::Event;

Event::Event() : type(NONE), description("") {} 
Event::Event(const EventType t, const char* desc) : type(t), description(desc) {}

Event::Event(const Event& e) : type(e.getType()), description(e.getDescription()) {}

Event::~Event() { /*delete description;*/ }

EventType Event::getType() const {
    return type;
}

const char* Event::getDescription() const {
    return description;
}
