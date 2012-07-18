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

#include "ass.h"
#include "utils/utils.h"

#include <itpp/itbase.h>
using itpp::vec;

NS_SVMACS_BEGIN

ASS::ASS(int samplerate) : Feature(samplerate, SPECTRAL) {}

ASS::~ASS() {}

const int INDEX = 2;

void ASS::extract(const vec& spectrum, vec& features) const {
    const int len = spectrum.length() - 1;

    // discard the 0-bin frequency
    vec absSpec = abs(spectrum.right(len));

    double summ = itpp::sum(absSpec);
    vec bins = linvec(1.0, static_cast<double>(len));

    double centroid = 0.0;
    double spread = 0.0;
    if (summ > 0.0) {
        centroid = itpp::sum(itpp::elem_mult(bins, absSpec)) / summ;
        spread = itpp::sum(itpp::elem_mult( itpp::sqr(bins - centroid), absSpec)) / summ;
    }

    features[INDEX] = spread;
    features[INDEX + 1] = centroid;
}

NS_SVMACS_END
