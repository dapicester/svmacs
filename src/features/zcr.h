/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ZCR_H
#define ZCR_H

#include "feature.h"
using namespace features;

namespace features {

class ZCR : public Feature {

public:
    ZCR(int samplerate, string name = "ZCR");
    ~ZCR();
    
    float* extract(const float frame[]) const;
};

}
    
#endif
