/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "feature.h"

#include <itpp/itsignal.h>
using namespace itpp;

namespace features {

class Processor {
    /// Sample rate (from Jackd)
    uint sampleRate;
    
    /// Frame length
    uint M;
    /// Frame overlap
    uint R;
    
    /// Number of feature extractors
    static const uint fsize = 2;
    
    /// Features extractors 
    Feature* features[fsize];
    
public:
    /// Constructor
    Processor(int sr);
    
    /// Destructor
    ~Processor();

    /** Process an audio frame and returns its features */
    float* process(const vec& frame);
};

}

#endif
