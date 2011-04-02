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

void MFCC::initFilterBank() {
    const double freqMin = double(0);
    const double freqMax = double(samplerate / 2);

    mat wts(nfilters, nfft);
    wts.zeros();

    vec tmp = "0 : " + lexical_cast<std::string > (nfilters + 1);

    // extract frequency of each fft bin
    vec fft_freqs = "0 : " + lexical_cast<std::string > (nfft - 1);
    fft_freqs = fft_freqs * static_cast<double>(samplerate) / nfft;

    double melMin = 2595 * itpp::logb(10, 1 + freqMin / 700);
    double melMax = 2595 * itpp::logb(10, 1 + freqMax / 700);

    vec bin_freqs = 700 * ( itpp::pow10((
                                      melMin + tmp / (nfilters + 1) * (melMax - melMin)
                                ) / 2595 ) - 1 );

    //vec bins = itpp::round(bin_freqs / samplerate * (nfft - 1)); FIXME: verificare

    for (int i = 0; i < nfilters; i++) {
        itpp::ivec idx = "0 1 2";
        vec freqs = bin_freqs(idx + i);

        // lower and upper slopes for all bins
        vec loslope = (fft_freqs - freqs[0]) / (freqs[1] - freqs[0]);
        vec hislope = (freqs[2] - fft_freqs) / (freqs[2] - freqs[1]);

        // ... then intersect them with each other and zero
        //MATLAB:  wts(i,:) = max(0,min(loslope, hislope));
        mat m1(2, nfft);
        m1.set_row(0, loslope);
        m1.set_row(1, hislope);

        mat m2(2, nfft);
        m2.zeros();
        m2.set_row(1, itpp::min(m1));

        wts.set_row(i, itpp::max(m2));
    }

    // Make sure 2nd half of FFT is zero
    // MATLAB:  wts(:, Nfft/2+1:Nfft) = 0;
    for (int i = 0; i < nfilters; i++) {
        for (int j = nfft/2; j < nfft; j++) {
            wts.set(i, j, 0.0);
        }
    }

    filterBank = wts;
}

void MFCC::extract(const vec& spectrum, vec& features) const {
    // critical bands energy
    mat energy = filterBank * spectrum;
    // bias to avoid log(0)
    energy += 1;

    int numFilters = filterBank.rows();

    // dichiarati come matrice sono in realta vettori
    mat a = "0 : " + lexical_cast<std::string > (ncoeffs);
    mat b = vec("1 : " + lexical_cast<std::string >(numFilters)) - 0.5;

    mat arg = a.hermitian_transpose() * b * (itpp::pi / numFilters);
    mat coeffs = itpp::cos(arg) * itpp::logb(10, energy);

    vec mfcc = coeffs.get_col(0).right(ncoeffs);
    for (int i = 0; i < ncoeffs; i++) {
        features[INDEX + i] = mfcc[i];
    }
}
