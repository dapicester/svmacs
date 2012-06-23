/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include "config.h"
#include <string>

NS_SVMACS_BEGIN

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
    Event(const EventType& t, const std::string& desc = "");
    Event(const Event& e);
    ~Event();
    
    /// Getter for the type property.
    EventType getType() const;
    
    /// Getter for the description property
    std::string getDescription() const ;
    
private: // TODO: add details, e.g. timestamp
    EventType type;
    const std::string description;
};

NS_SVMACS_END

#endif
