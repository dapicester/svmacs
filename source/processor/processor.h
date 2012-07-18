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

#ifndef SVMACS_PROCESSOR_H
#define SVMACS_PROCESSOR_H

#include "config.h"
#include <itpp/base/vec.h>
#include <boost/ptr_container/ptr_vector.hpp>

NS_SVMACS_BEGIN

class Feature;

/**
 * Audio processor.
 * Class processing the input audio frames for feature extraction.
 */
class Processor {
public:

    /**
     * Constructor.
     * @param sr sample rate
     */
    Processor(int sr);

    /// Destructor.
    ~Processor();

    /**
     * Process the input for feature extraction.
     * @param frame the input audio frame
     * @return a vector containing the extracte audio features
     */
    itpp::vec process(const itpp::vec& frame);

private:

    int sampleRate; ///< Sample rate.
    itpp::vec win;  ///< Analisys window.
    int M;          ///< Frame length.
    int R;          ///< Frame overlap.

    /// Feature extractors.
    boost::ptr_vector<Feature> extractors;
};

NS_SVMACS_END

#endif // SVMACS_PROCESSOR_H
