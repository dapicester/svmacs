/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef ENERGY_H
#define ENERGY_H

#include "feature.h"

/**
 * Energy audio feature.
 * TODO: definition
 */
class Energy : public Feature {
public:
    Energy(int samplerate);
    ~Energy();
    
    /// Compute the energy for the given frame.
    void extract(const itpp::vec& frame, itpp::vec* features) const;
};
    
#endif
