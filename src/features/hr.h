/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef HR_H
#define HR_H

#include "feature.h"
using namespace features;

namespace features {

/// Extract the Harmonic Ratio
class HR : public Feature {
    
public:
    HR(int samplerate, string name = "HR");
    ~HR();
    
    Type getType() const;
    
    /** 
     * Compute the HR for the given frame
     * \param frame the audio samples
     */
     void extract(const vec& frame, vec& features) const;
};

}

#endif
