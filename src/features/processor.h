/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <features/feature.h>

namespace features {

/** 
 * Class processing the input audio frames for feature extraction.
 */
class Processor {
public:
    Processor(int sr);
    ~Processor();
    
    /**
     * Process the input for feature extraction. 
     * @param frame the input audio frame
     * @return a vector containing the extracte audio features
     */
    itpp::vec process(const itpp::vec& frame);
    
private: 
    /// Sample rate (from Jackd)
    unsigned int sampleRate;
    
    /// Window
    itpp::vec win;
    
    /// Frame length
    unsigned int M;
    /// Frame overlap
    unsigned int R;
    
    /// Number of feature extractors
    static const unsigned int N_EXTRACTORS = 6;
    /// Features extractors 
    Feature* features[N_EXTRACTORS];
    //Feature* features; // TODO: using containers from stdlib
};

}

#endif
