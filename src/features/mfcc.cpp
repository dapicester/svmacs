/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "mfcc.h"

#include <itpp/itbase.h>
using itpp::vec;
using itpp::mat;

#define RLOG_COMPONENT "mfcc"
#include <rlog/rlog.h>

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

MFCC::MFCC(int samplerate, int n, int nf, int nc)
        : Feature(samplerate, SPECTRAL), nfft(n), nfilters(nf), ncoeffs(nc) {
    name = "MFCC";
    initFilterBank();
}

MFCC::~MFCC() {
}

static const int INDEX = 6;

void MFCC::extract(const vec& spectrum, vec& features) const {
    /* critical bands energy */
    mat energy = filterBank * spectrum;
    /* bias to avoid log(0) */
    energy += 1;

    /* declared as matrices but actually vectors */
    mat a = "0 : " + lexical_cast<std::string > (ncoeffs);
    mat b = vec("1 : " + lexical_cast<std::string >(nfilters)) - 0.5;

    mat arg = a.hermitian_transpose() * b * (itpp::pi / nfilters);
    mat coeffs = itpp::cos(arg) * itpp::log10(energy);

    vec mfcc = coeffs.get_col(0);
    /* double logEnergy = mfcc[0]; */
    for (int i = 0; i < ncoeffs; i++) { /* discard logEnergy */
        features[INDEX + i] = mfcc[i+1];
    }
}
