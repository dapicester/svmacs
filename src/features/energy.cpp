/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "energy.h"
using namespace features;

#define RLOG_COMPONENT "energy"
#include <rlog/rlog.h>

Energy::Energy(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

Energy::~Energy() {}

vec Energy::extract(const vec& frame) const {
    const int len = frame.length();
    
    vec square = sqr(abs(frame));
    
    double energy = sum(square);
    //PRINT(energy)

    energy = energy / len * getSamplerate();
    //PRINT(energy)
    
    vec ret(&energy, 1);
    //PRINT(ret);
    return ret;
}
