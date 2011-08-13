/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef HR_H
#define HR_H

#include "feature.h"

/**
 * Harmonic Ratio audio feature.
 * TODO: definition
 */
class HR : public Feature {
public:
    HR(int samplerate);
    ~HR();
    
    /// Compute the HR for the given audio frame.
    void extract(const itpp::vec& frame, itpp::vec* features) const;
};

#endif
