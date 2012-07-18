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

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "config.h"
#include "model/event.h"

#include <boost/noncopyable.hpp>
#include <itpp/base/vec.h>

NS_SVMACS_BEGIN

/**
 * Classifier interface.
 */
class Classifier : private boost::noncopyable {
public:

    virtual ~Classifier() {}

    /**
     * Process the audio features for detection
     * and classification of events.
     * @param features the feature vector
     * @return The type of event detected.
     * @see Event::Type
     */
    virtual Event::Type classify(const itpp::vec& features) const = 0;
};

NS_SVMACS_END

#endif
