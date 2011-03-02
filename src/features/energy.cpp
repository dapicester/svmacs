/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include <features/energy.h>
using namespace features;

#include <itpp/itbase.h>

#define RLOG_COMPONENT "energy"
#include <rlog/rlog.h>

Energy::Energy(int samplerate) : Feature(samplerate, TEMPORAL) {
    setName("Energy");
}

Energy::~Energy() {}

void 
Energy::extract(const vec& frame, vec& features) const {
    const int len = frame.length();
    
    vec square = itpp::sqr(itpp::abs(frame));
    
    double energy = itpp::sum(square);
    
    energy = energy / len * samplerate;
    
    features = itpp::concat(features, energy);
}
