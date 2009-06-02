/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "feature.h"

#include <itpp/base/vec.h>
using itpp::vec;

namespace features {

class Processor {
    /// Sample rate (from Jackd)
    uint sampleRate;
    
    /// Default window length in seconds (25ms)
    static const double WIN_LEN = 0.025;
    /// Default percentage of windows overlap (50%)
    static const double WIN_OVL = 0.5;
    
    /// Windows
    vec win;
    
    /// Frame length
    uint M;
    /// Frame overlap
    uint R;
    
    /// Number of frequency bins
    static const int N_FFT = 1024;
    /// Number of MFCC filters
    static const int N_MFCC_FILTERS = 24; 
    
    /// Number of feature extractors
    static const uint N_EXCTRACTORS = 6;
    /// Features extractors 
    Feature* features[N_EXCTRACTORS];
    
    /// Number of features
    static const uint N_FEATURES = 12;
    
public:
    /// Constructor
    Processor(int sr);
    
    /// Destructor
    ~Processor();
    
    /** Process an audio frame and returns its features */
    vec process(const vec& frame);
};

}

#endif
