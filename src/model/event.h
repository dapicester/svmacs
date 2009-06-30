/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef EVENT_H
#define EVENT_H

#include "classifier.h"
using model::EventType;

namespace model {

class Event {
    EventType type;
    const char* description;
    
public:
    Event();
    Event(const EventType t, const char* desc = "");
    Event(const Event& e);
    ~Event();
    
    EventType getType() const;
    
    const char* getDescription() const ;

};

}

#endif
