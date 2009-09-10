/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ENERGY_H
#define ENERGY_H

#include "feature.h"

namespace features {

/// Extract the energy
class Energy : public Feature {

public:
    Energy(int samplerate, string name = "Energy");
    ~Energy();
    
    Type getType() const;
    
    /**
     * Compute the energy for the given frame
     * \param frame the audio samples
     */
    void extract(const vec& frame, vec& features) const;
};

}
    
#endif
