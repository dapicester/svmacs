/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef ZCR_H
#define ZCR_H

#include "feature.h"

/**
 * Zero-Crossing-Rate audio feature.
 * TODO: definition
 */
class ZCR : public Feature {
public:
    ZCR(int samplerate);
    ~ZCR();
    
    /// Compute the ZCR for the given frame.
    void extract(const itpp::vec& frame, itpp::vec* features) const;
};

#endif
