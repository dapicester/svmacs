/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "processor.h"

#include "features/feature.hpp"
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

vec
Processor::process(const vec& frame) {
    int L = frame.length();
    int Nframes = (L - R)/(M - R);

    //vec frame = itpp::concat(frame, flipud(frame.right(R)));
    //rDebug("frame padded to length %d", pframe.length());

    int i = 0;
    mat featureMatrix = itpp::zeros(Nframes, N_FEATURES);
#pragma omp parallel for ordered shared(featureMatrix) private(i) schedule(dynamic,3)
    for (int counter = 0; counter < Nframes; counter++) {
        vec tmp = frame.mid(i, M);

        // windowing
        vec current = itpp::elem_mult(tmp, win);
        vec spectrum = itpp::abs( itpp::fft( itpp::to_cvec(current), N_FFT ) ).left(N_FFT/2);

        // extracting
        vec features = itpp::zeros(N_FEATURES);
        for (boost::ptr_vector<Feature>::size_type j = 0u; j < extractors.size(); j++) {
            switch (extractors[j].getType()) {
            case Feature::TEMPORAL:
                extractors[j].extract(current, features);
                break;
            case Feature::SPECTRAL:
                extractors[j].extract(spectrum, features);
                break;
            default: // this should never occur
                rError("unknown feature type: (%i)", extractors[j].getType());
            }
        }

        //rDebug("feature vector: %s", itpp::to_str(features).c_str());
        featureMatrix.set_row(counter, features);
        i += M - R - 1;
    }
    //rDebug("feature matrix:\n %s", itpp::to_str(featureMatrix).c_str());

    // data reduction
    vec vout = itpp::zeros(N_FEATURES);
#pragma omp parallel for shared(vout) schedule(dynamic,2)
    for (int i = 0; i < N_FEATURES; i++) {
        vout.set(i, itpp::mean(featureMatrix.get_col(i)) );
    }

    //rDebug("final feature vector: %s", itpp::to_str(vout).c_str());
    return vout;
}

NS_SVMACS_END
