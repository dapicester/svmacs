/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "srf.h"
using namespace features;

#include <itpp/base/math/elem_math.h>
using itpp::sqr;
#include <itpp/base/matfunc.h>
using itpp::sum;

#define RLOG_COMPONENT "srf"
#include <rlog/rlog.h>

#define PRINT(X) cout << #X << ": " << X <<endl;
#include <iostream>
using namespace std;

SRF::SRF(int samplerate, string name) : Feature() {
    setSamplerate(samplerate);
    setName(name);
}

SRF::~SRF() {}

Type SRF::getType() const { return SPECTRAL; }

void SRF::extract(const vec& frame, vec& features) const {
    const int len = frame.length();
    
    vec spectrum2 = sqr(frame);
    
    double threshold = ALPHA * sum(spectrum2);
    
    double K = 0.0;
    for (int k=1; k<len; k++) {
        //FIXME constrollare
        double summ = sum(spectrum2.left(k));
        if ( summ > threshold) {
             K = k;
             break;
        }
    }
    features = concat(features, K);
}
