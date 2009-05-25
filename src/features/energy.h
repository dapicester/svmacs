/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ENERGY_H
#define ENERGY_H

#include "feature.h"
using namespace features;

#include <itpp/itsignal.h>
using namespace itpp;

namespace features {

/// Extract the energy
class Energy : public Feature {

public:
    Energy(int samplerate, string name = "Energy");
    ~Energy();
    
    /** Compute the energy for the given frame
     * \param frame the audio samples
     */
    vec extract(const vec& frame) const;
};

}
    
#endif
