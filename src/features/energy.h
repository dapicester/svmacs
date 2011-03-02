/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ENERGY_H
#define ENERGY_H

#include <features/feature.h>

namespace features {

/**
 * Energy audio feature.
 * TODO: definition
 */
class Energy : public Feature {
  
  public:
    
    Energy(int samplerate);
    
    ~Energy();
    
    /// Compute the energy for the given frame.
    void extract(const vec& frame, vec& features) const;
    
};

}
    
#endif
