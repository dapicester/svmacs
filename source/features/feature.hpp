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

#ifndef SVMACS_FEATURE_HPP
#define SVMACS_FEATURE_HPP

#include "config.h"
#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>

NS_SVMACS_BEGIN

/**
 * Abstract base class for feature extractors.
 */
class Feature : private boost::noncopyable {
public:

    /**
     * Enumeration for feature types.
     */
    enum Type {
        /// Feature based on the signal time-representation.
        TEMPORAL,
        /// Feature based on the signal frequency-representation.
        SPECTRAL
    };

    /**
     * Constructor.
     * @param sr sample rate
     * @param t feature type
     */
    Feature(int sr, Type t) : samplerate(sr), type(t) {}

    /// Destructor.
    virtual ~Feature() {}

    /// Getter for the type property.
    Type getType() const { return type; }

    /**
     * Processes an audio frame and returns the computed features.
     * @param data data to be processed
     * @param[out] features vector into which insert the computed feature
     */
    virtual void extract(const itpp::vec& data, itpp::vec& features) const = 0;

protected:

    const int samplerate; ///< The sample rate;
    const Type type;      ///< The feature type.
};

NS_SVMACS_END

#endif // SVMACS_FEATURE_HPP
