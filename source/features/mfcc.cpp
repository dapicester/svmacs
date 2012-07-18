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

#include "mfcc.h"
#include "config.h"
#include "utils/utils.h"

#include <itpp/itbase.h>
using itpp::vec;
using itpp::mat;

NS_SVMACS_BEGIN

MFCC::MFCC(int samplerate, int n, int nf, int nc)
        : Feature(samplerate, SPECTRAL), nfft(n), nfilters(nf), ncoeffs(nc) {
    initFilterBank();
}

MFCC::~MFCC() {}

const int INDEX = 6;

void MFCC::extract(const vec& spectrum, vec& features) const {
    // critical bands energy
    mat energy = filterBank * spectrum;
    // bias to avoid log(0)
    energy += 1;

    // declared as matrices but actually vectors
    mat a(linvec(0.0, static_cast<double>(ncoeffs)));
    mat b(linvec(1.0, static_cast<double>(nfilters)));

    mat arg = a.transpose() * (b - 0.5) * (itpp::pi / nfilters);
    mat coeffs = itpp::cos(arg) * itpp::log10(energy);

    vec mfcc = coeffs.get_col(0);
    // double logEnergy = mfcc[0];
    for (int i = 0; i < ncoeffs; i++) { // discard logEnergy
        features[INDEX + i] = mfcc[i+1];
    }
}

NS_SVMACS_END
