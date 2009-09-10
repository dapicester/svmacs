/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "energy.h"
using namespace features;

#include <itpp/itbase.h>

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
    
    vec square = itpp::sqr(itpp::abs(frame));
    
    double energy = itpp::sum(square);
    
    energy = energy / len * getSamplerate();
    
    features = concat(features, energy);
}
