/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef ZCR_H
#define ZCR_H

#include <features/feature.h>

namespace features {

/**
 * Zero-Crossing-Rate audio feature.
 * TODO: definition
 */
class ZCR : public Feature {
public:
    ZCR(int samplerate);
    ~ZCR();
    
    /// Compute the ZCR for the given frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

}
    
#endif
