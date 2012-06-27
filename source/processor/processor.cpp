/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "processor.h"

#include "features/feature.h"
#include "features/zcr.h"
#include "features/energy.h"
#include "features/ass.h"
#include "features/srf.h"
#include "features/hr.h"
#include "features/mfcc.h"

using itpp::vec;
using itpp::mat;

#include "utils/utils.h"

#include <itpp/itsignal.h>
#include <itpp/stat/misc_stat.h>

#define RLOG_COMPONENT "processor"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

/// Default window length in seconds (25ms)
const double WIN_LEN = 0.025;
/// Default percentage of windows overlap (50%)
const double WIN_OVL = 0.5;

/// Number of frequency bins
const int N_FFT = 1024;
/// Number of MFCC filters
const int N_MFCC_FILTERS = 24;
/// Number of MFCC coefficients
const int N_MFCC_COEFFS = 6;

/// Number of features
const int N_FEATURES = 12;

Processor::Processor(int sr) : sampleRate(sr) {
    // initialize attributes
    M = itpp::floor_i(WIN_LEN * sampleRate);    // TODO non serve floor
    R = itpp::floor_i(WIN_OVL * M);             // TODO non serve floor
    win = itpp::hamming(M);
    rDebug("segmenting using %d samples hamming window, %d samples overlap", M, R);

    // initialize workers
    extractors.push_back(new ZCR(sampleRate));
    extractors.push_back(new Energy(sampleRate));
    extractors.push_back(new ASS(sampleRate));
    extractors.push_back(new SRF(sampleRate));
    extractors.push_back(new HR(sampleRate));
    extractors.push_back(new MFCC(sampleRate, N_FFT-1, N_MFCC_FILTERS, N_MFCC_COEFFS))    ;
    rDebug("workers created");

    rInfo("Processor created");
}

Processor::~Processor() {
    rInfo("Processor correctly destroyed");
}

vec Processor::process(const vec& frame) {
    int L = frame.length();
    int Nframes = (L - R)/(M - R);

    //vec frame = itpp::concat(frame, flipud(frame.right(R)));
    //rDebug("frame padded to length %d", pframe.length());

    mat featureMatrix = itpp::zeros(Nframes, N_FEATURES);
    for (int counter = 0, i = 0; counter < Nframes; counter++, i += M - R - 1) {
        vec tmp = frame.mid(i, M);

        // windowing
        vec current = itpp::elem_mult(tmp, win);
        vec spectrum = itpp::abs( itpp::fft( itpp::to_cvec(current), N_FFT ) ).left(N_FFT/2);

        // extracting
        vec features = itpp::zeros(N_FEATURES);
#pragma omp parallel for
        for (boost::ptr_vector<Feature>::size_type j = 0u; j < extractors.size(); j++) {
            switch (extractors[j].getType()) {
            case TEMPORAL:
                extractors[j].extract(current, &features);
                break;
            case SPECTRAL:
                extractors[j].extract(spectrum, &features);
                break;
            default: // this should never occur
                rError("unknown feature type: (%i)", extractors[j].getType());
            }
        }

        //rDebug("feature vector: %s", itpp::to_str(features).c_str());
        featureMatrix.set_row(counter, features);
    }
    //rDebug("feature matrix:\n %s", itpp::to_str(featureMatrix).c_str());

    // data reduction
    vec vout = itpp::zeros(N_FEATURES);
    for (int i = 0; i < N_FEATURES; i++) {
        vout.set(i, itpp::mean(featureMatrix.get_col(i)) );
    }

    //rDebug("final feature vector: %s", itpp::to_str(vout).c_str());
    return vout;
}

NS_SVMACS_END
