/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "energy.h"
using namespace features;

#define RLOG_COMPONENT "zcr"
#include <rlog/rlog.h>

Energy::Energy(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

Energy::~Energy() {}

vec Energy::extract(const vec& frame) const {
    vec out(1);
    const int len = frame.length();
    
    vec square = sqr(abs(frame));
    
    double energy = 0;
    for (int i=0; i<len; i++)
        energy += square[i];
    
    energy = energy / len * getSamplerate();
    out.set(energy,0);
    
    return out;
}
