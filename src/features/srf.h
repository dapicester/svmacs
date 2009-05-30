/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SRF_H
#define SRF_H

#include "feature.h"
using namespace features;

namespace features {

/// Extract the Spectral Roll-off
class SRF : public Feature {
    /// Roll-off threshold (percentage)
    static const double ALPHA = 0.93;
    
public:
    SRF(int samplerate, string name = "SRF");
    ~SRF();
    
    Type getType() const;
    
    /** 
     * Compute the SRF for the given spectrum
     * \param frame the audio spectrum
     */
     void extract(const vec& frame, vec& features) const;
};

}

#endif
