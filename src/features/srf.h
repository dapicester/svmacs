/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SRF_H
#define SRF_H

#include"feature.h"

NS_SVMACS_BEGIN

/**
 * Spectral Roll-off audio feature.
 * TODO: definition
 */
class SRF : public Feature {
public:
    SRF(int samplerate);
    ~SRF();
    
    /// Compute the SRF for the given spectrum frame.
    void extract(const itpp::vec& frame, itpp::vec* features) const;
};

NS_SVMACS_END

#endif
