/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ASS_H
#define ASS_H

#include "feature.h"
using namespace features;

#include <itpp/itsignal.h>
using namespace itpp;

namespace features {

/// Extract the Audio Spectral Spread and the Audio Spectral Centroid
class ASS : public Feature {

public:
    ASS(int samplerate, string name = "ASS");
    ~ASS();
    
    /** 
     * Compute the ASS and the ASC for the given spectrum
     * \param frame the audio spectrum
     */
    vec extract(const vec& frame) const;
};

}

#endif
