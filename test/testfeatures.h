/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef TEST_FEATURES_H
#define TEST_FEATURES_H

#define PRINT(X) cout << #X << ": " << X <<endl;

#include "feature.h"
using namespace features;

#include "convert.h"
using namespace utils;

#include <cmath>
#include <itpp/itsignal.h>
using namespace itpp;

#include <iostream>
using namespace std;

static const int N_FFT = 1024;

/// Get a linear vector
inline vec getTime(double start, double end, double step = 1) {
    string s = stringify(start) + ":" + stringify(step) + ":" + stringify(end) ;
    vec out(s);
    return out;
}

/// Get a test signal
inline vec getSignal(const vec& time, const double frequency, const double noise = 0.0) {
    return sin(m_2pi * frequency * time ) + sqrt(noise) * randn(time.length());
}

/// Get a silence signal
inline vec getSilence(const vec& time) {
    vec silence(time.size());
    silence.zeros();
    return silence;
}

/// Test a feature on a given signal
void test(const vec& signal, const Feature* feature) {
    cout << "Testing " << feature->getName() << " ..." << endl;
    vec val = feature->extract(signal);
    PRINT(val);
    cout << "done." << endl;
}

#endif
