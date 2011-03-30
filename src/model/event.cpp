/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "event.h"

Event::Event() : type(NONE), description("") {} 
Event::Event(const EventType& t, const std::string& desc) : type(t), description(desc) {}

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
