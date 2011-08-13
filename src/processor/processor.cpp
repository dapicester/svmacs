/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "config.h"
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

/// Default window length in seconds (25ms)
static const double WIN_LEN = 0.025;
/// Default percentage of windows overlap (50%)
static const double WIN_OVL = 0.5;
    
/// Number of frequency bins
static const int N_FFT = 1024;
/// Number of MFCC filters
static const int N_MFCC_FILTERS = 24; 
/// Number of MFCC coefficients
static const int N_MFCC_COEFFS = 6;

/// Number of features
static const int N_FEATURES = 12;

Processor::Processor(int sr) : sampleRate(sr) {
    // initialize attributes
    M = itpp::floor_i(WIN_LEN * sampleRate);    // TODO non serve floor
    R = itpp::floor_i(WIN_OVL * M);             // TODO non serve floor
    win = itpp::hamming(M);
    rDebug("segmenting using %d samples hamming window, %d samples overlap", M, R);
    
    // initialize workers
    workers.push_back(new Worker(new ZCR(sampleRate)));
    workers.push_back(new Worker(new Energy(sampleRate)));
    workers.push_back(new Worker(new ASS(sampleRate)));
    workers.push_back(new Worker(new SRF(sampleRate)));
    workers.push_back(new Worker(new HR(sampleRate)));
    workers.push_back(new Worker(new MFCC(sampleRate, N_FFT-1, N_MFCC_FILTERS, N_MFCC_COEFFS)));
    rDebug("workers created");
    
    rInfo("Processor created");
}

Processor::~Processor() {
    rInfo("Processor correctly destroyed");
}

vec Processor::process(const vec& frame) {
    //rDebug("process called ...");
    
    int L = frame.length();
    //rDebug("L: %d samples", L);
    
    int Nframes = (L - R)/(M - R);
    //rDebug("Nframes: %d", Nframes);
    
    //vec frame = itpp::concat(frame, flipud(frame.right(R)));
    //rDebug("frame padded to length %d", pframe.length());

    mat featureMatrix = itpp::zeros(Nframes, N_FEATURES);
    for (int counter = 0, i = 0; counter < Nframes; counter++, i += M - R - 1) {
        //rDebug("reading (%d) samples at index [%d+%d]", counter, i, M);
        vec tmp = frame.mid(i, M);
        
        //rDebug("windowing");
        vec current = itpp::elem_mult(tmp, win);
        vec spectrum = itpp::abs( itpp::fft( itpp::to_cvec(current), N_FFT ) ).left(N_FFT/2);
           
        //rDebug("extracting");
        vec features = itpp::zeros(N_FEATURES);
        for (boost::ptr_vector<Worker>::size_type j = 0u; j < workers.size(); j++) {
            //rDebug("extracting %s", extractors[j]->getName().c_str());
            switch (workers[j].getFeatureType()) {
            case TEMPORAL:
                workers[j].start(current, &features); 
                break;
            case SPECTRAL: 
                workers[j].start(spectrum, &features); 
                break;
            default: // this should never occur
                rError("unknown feature type: (%i)", workers[j].getFeatureType());
            }
            //rDebug("started worker [%d]", j);
        }
        // waiting for termination
        for (boost::ptr_vector<Worker>::size_type j = 0u; j < workers.size(); j++) {
            //rDebug("waiting for worker [%d]", j);
            workers[j].join();
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
