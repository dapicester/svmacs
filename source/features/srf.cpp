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

#include "srf.h"

#include <itpp/itbase.h>
using itpp::vec;

NS_SVMACS_BEGIN

/// Roll-off threshold (percentage)
const double ALPHA = 0.93;

SRF::SRF(int samplerate) : Feature(samplerate, SPECTRAL) {}

SRF::~SRF() {}

const int INDEX = 4;

void SRF::extract(const vec& spectrum, vec& features) const {
    const int len = spectrum.length();

    vec spectrum2 = itpp::sqr(itpp::abs(spectrum));
    double threshold = ALPHA * itpp::sum(spectrum2);

    double K = 0.0;
    double summ = 0.0;
    for (int k = 1; k < len; k++) {
        summ = itpp::sum(spectrum2.left(k));
        //if ( summ > threshold) { XXX: this is correct
        if (summ < threshold) {
             K = k;
             break;
        }
    }

    features[INDEX] = K;
}

NS_SVMACS_END
