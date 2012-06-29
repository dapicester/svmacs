/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

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
