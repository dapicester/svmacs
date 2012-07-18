/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef SVMACS_EVENT_H
#define SVMACS_EVENT_H

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
    // TODO: add details, e.g. timestamp (Boost posix_time)
    const std::string description;
};

NS_SVMACS_END

#endif // SVMACS_EVENT_H
