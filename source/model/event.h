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
    NONE,       ///< No Event
    GUNSHOT,    ///< Gunshot
    SCREAM,     ///< Scream
    GLASS       ///< Breaking glass
};

/**
 * Detected event.
 */
class Event {
public:
    /// Constructor.
    Event(const EventType t = NONE, const std::string& desc = "")
        : type(t), description(desc) {}

    /// Copy constructor.
    Event(const Event& e)
        : type(e.getType()), description(e.getDescription()) {}

    /// Destructor.
    ~Event() {}

    /// Getter for the type property.
    EventType getType() const {
        return type;
    }

    /// Getter for the description property
    std::string getDescription() const {
        return description;
    }

private:

    /// The event type.
    EventType type;

    /// A descriptive string.
    // TODO: add details, e.g. timestamp
    const std::string description;
};

NS_SVMACS_END

#endif
