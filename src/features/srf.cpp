/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "config.h"
#include "srf.h"

#include <itpp/itbase.h>
using itpp::vec;

#define RLOG_COMPONENT "srf"
#include <rlog/rlog.h>

/// Roll-off threshold (percentage)
static const double ALPHA = 0.93;

SRF::SRF(int samplerate) : Feature(samplerate, SPECTRAL) {
    name = "SRF";
}

SRF::~SRF() {}

static const int INDEX = 4;

void SRF::extract(const vec& spectrum, vec* features) const {
    const int len = spectrum.length();

    vec spectrum2 = itpp::sqr(itpp::abs(spectrum)); // TODO togliere abs?
    double threshold = ALPHA * itpp::sum(spectrum2);

    double K = 0.0;
    for (int k = 1; k < len; k++) {
        double summ = itpp::sum(spectrum2.left(k));
        //if ( summ > threshold) { XXX: this is correct
        if (summ < threshold) {
             K = k;
             break;
        }
    }

    (*features)[INDEX] = K;
}
