/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "zcr.h"
using namespace features;

#include <itpp/base/math/elem_math.h>

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

ZCR::ZCR(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

ZCR::~ZCR() {}

vec ZCR::extract(const vec& frame) const {
    vec out(1);
    const int len = frame.length();
    
    vec sgn = sign(frame);
    vec diff = sgn - concat(sgn[0],sgn.left(sgn.length()));
    
    uint cont = 0;
    for (int i=0; i<diff.length(); i++)
        if (diff[i] == 0)
            cont++;
    //FIXME test
    double zcr = ((double) cont)/((double)len) * getSamplerate();
    #ifdef ENABLE_DEBUG
    rDebug("zcr: %f", zcr);
    #endif
    
    out.set(zcr,0);
    
    return out;
}
