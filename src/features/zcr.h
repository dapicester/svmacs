/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ZCR_H
#define ZCR_H

#include "feature.h"

namespace features {

/// Extract the Zero-Crossing-Rate
class ZCR : public Feature {

public:
    ZCR(int samplerate, string name = "ZCR");
    ~ZCR();
    
    Type getType() const;
    
    /** Compute the ZCR for the given frame
     * \param frame the audio samples
     */
    void extract(const vec& frame, vec& features) const;
};

}
    
#endif
