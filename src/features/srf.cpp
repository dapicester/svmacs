/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <features/srf.h>
using namespace features;

#include <itpp/base/math/elem_math.h>
#include <itpp/base/matfunc.h>

#define RLOG_COMPONENT "srf"
#include <rlog/rlog.h>

SRF::SRF(int samplerate) : Feature(samplerate, SPECTRAL) {
    setName("SRF");
}

SRF::~SRF() {}

void
SRF::extract(const vec& frame, vec& features) const {
    const int len = frame.length();
    
    vec spectrum2 = itpp::sqr(frame);
    
    double threshold = ALPHA * itpp::sum(spectrum2);
    
    double K = 0.0;
    for (int k=1; k<len; k++) {
        double summ = itpp::sum(spectrum2.left(k));
        //FIXME va col < (sbagliata la versione matlab)
        //if ( summ > threshold) {
        if ( summ < threshold) {
             K = k;
             break;
        }
    }
    features = itpp::concat(features, K);
}
