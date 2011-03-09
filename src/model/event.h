/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <string>

namespace model {
    
/** 
 * Type of detected event.
 */    
enum EventType {
    NONE, GUNSHOT, SCREAM, GLASS
};

/**
 * Detected event.
 */
class Event { 
public:
    Event();
    Event(const EventType t, const char* desc = "");
    Event(const Event& e);
    ~Event();
    
    /// Getter for the type property.
    EventType getType() const;
    
    /// Getter for the description property
    std::string getDescription() const ;
    
private:
    EventType type;
    const std::string description;
};

}

#endif
