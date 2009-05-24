/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef ZCR_H
#define ZCR_H

#include "feature.h"
using namespace features;

#include <itpp/itsignal.h>
using namespace itpp;

namespace features {

class ZCR : public Feature {

public:
    ZCR(int samplerate, string name = "ZCR");
    ~ZCR();
    
    vec extract(const vec& frame) const;
};

}
    
#endif
