/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "zcr.h"
using namespace features;

#include <itpp/base/math/elem_math.h>
using itpp::sign;

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

ZCR::ZCR(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

ZCR::~ZCR() {}

inline Type ZCR::getType() const { return TEMPORAL; }

void ZCR::extract(const vec& frame, vec& features) const {
    const int len = frame.length();

    vec sgn = sign(frame); 
    
    double cont = 0;
    for (int  i = 0; i < len - 2; i++) {
        if ( (sgn[i+1] - sgn[i]) != 0 )
             cont++;
    }

    double zcr = cont / len * getSamplerate();
    
    features = concat(features, zcr); 
}
