/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "energy.h"
using namespace features;

#include <itpp/base/math/elem_math.h>
using itpp::abs;
using itpp::sqr;
#include <itpp/base/matfunc.h>
using itpp::sum;

#define RLOG_COMPONENT "energy"
#include <rlog/rlog.h>

Energy::Energy(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

Energy::~Energy() {}

inline Type Energy::getType() const { return TEMPORAL; }

void Energy::extract(const vec& frame, vec& features) const {
    const int len = frame.length();
    
    vec square = sqr(abs(frame));
    
    double energy = sum(square);
    
    energy = energy / len * getSamplerate();
    
    features = concat(features, energy);
}
