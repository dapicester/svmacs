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
 * Detected event.
 */
class Event {
public:

    /**
     * Type of detected event.
     */
    enum Type {
        NONE = 0,   ///< No Event
        GUNSHOT,    ///< Gunshot
        SCREAM,     ///< Scream
        GLASS       ///< Breaking glass
    };

    /// Constructor.
    Event(const Type t = NONE, const std::string& desc = "")
        : type(t), description(desc) {}

    /// Copy constructor.
    Event(const Event& e)
        : type(e.getType()), description(e.getDescription()) {}

    /// Destructor.
    ~Event() {}

    /// Getter for the type property.
    Type getType() const {
        return type;
    }

    /// Getter for the description property
    std::string getDescription() const {
        return description;
    }

private:

    /// The event type.
    Type type;

    /// A descriptive string.
    // TODO: add details, e.g. timestamp
    const std::string description;
};

NS_SVMACS_END

#endif
