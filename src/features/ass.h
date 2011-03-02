/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ASS_H
#define ASS_H

#include <features/feature.h>

namespace features {

/**
 * Audio Spectral Spread and Audio Spectral Centroid audio features.
 * TODO: definitions
 */
class ASS : public Feature {

  public:
    
    ASS(int samplerate);
    
    ~ASS();
    
    /// Compute the ASS and the ASC for the given spectrum frame.
    void extract(const vec& frame, vec& features) const;
    
};

}

#endif
