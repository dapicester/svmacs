/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ENERGY_H
#define ENERGY_H

#include "feature.h"
using namespace features;

namespace features {

class Energy : public Feature {

public:
    Energy(int samplerate, string name = "Energy");
    ~Energy();
    
    float* extract(const float frame[]) const;
};

}
    
#endif
