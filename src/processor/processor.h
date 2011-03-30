/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef PROCESSOR_H
#define PROCESSOR_H

class Feature;

#include <itpp/base/vec.h>
#include <boost/ptr_container/ptr_vector.hpp>

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
    int sampleRate;
    
    /// Window
    itpp::vec win;
    
    /// Frame length
    int M;
    /// Frame overlap
    int R;
    
    /// Features extractors 
    boost::ptr_vector<Feature> extractors;
};

#endif
