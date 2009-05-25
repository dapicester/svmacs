/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ZCR_H
#define ZCR_H

#include "feature.h"
using namespace features;

#include <itpp/itsignal.h>
using namespace itpp;

namespace features {

/// Extract the Zero-Crossing-Rate
class ZCR : public Feature {

public:
    ZCR(int samplerate, string name = "ZCR");
    ~ZCR();
    
    /** Compute the ZCR for the given frame
     * \param frame the audio samples
     */
    vec extract(const vec& frame) const;
};

}
    
#endif
