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
    
    /// Constructor
    Processor(int sr);
    
    /// Destructor
    ~Processor();
    
    /**
     * Process the input for feature extraction. 
     * @param frame the input audio frame
     * @return a vector containing the extracte audio features
     */
    vec process(const vec& frame);
    
  private: 
    
    /// Sample rate (from Jackd)
    unsigned int sampleRate;
    
    /// Default window length in seconds (25ms)
    static const double WIN_LEN = 0.025;
    /// Default percentage of windows overlap (50%)
    static const double WIN_OVL = 0.5;
    
    /// Window
    vec win;
    
    /// Frame length
    unsigned int M;
    /// Frame overlap
    unsigned int R;
    
    /// Number of frequency bins
    static const int N_FFT = 1024;
    /// Number of MFCC filters
    static const int N_MFCC_FILTERS = 24; 
    
    /// Number of feature extractors
    static const unsigned int N_EXTRACTORS = 6;
    /// Features extractors 
    Feature* features[N_EXTRACTORS];
    //Feature* features; // TODO: using containers from stdlib
    
    /// Number of features
    static const unsigned int N_FEATURES = 12;

};

}

#endif
