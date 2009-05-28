/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "feature.h"

#include <itpp/itbase.h>
using namespace itpp;

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
    
    /// Number of feature extractors
    static const uint N_FEAT = 3;

    /// Features extractors 
    Feature* features[N_FEAT];

    /// Number of features
    static const uint N_FEATURES = 4;
    
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
