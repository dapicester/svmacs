/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef HR_H
#define HR_H

#include <features/feature.h>

namespace features {

/**
 * Harmonic Ratio audio feature.
 * TODO: definition
 */
class HR : public Feature {
  
  public:
    
    HR(int samplerate);
    
    ~HR();
    
    /// Compute the HR for the given audio frame.
    void extract(const vec& frame, vec& features) const;
    
};

}

#endif
