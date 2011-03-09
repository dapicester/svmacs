/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SRF_H
#define SRF_H

#include <features/feature.h>

namespace features {

/**
 * Spectral Roll-off audio feature.
 * TODO: definition
 */
class SRF : public Feature {
public:
    SRF(int samplerate);
    ~SRF();
    
    /// Compute the SRF for the given spectrum frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

}

#endif
