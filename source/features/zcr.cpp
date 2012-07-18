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

#include "zcr.h"

#include <itpp/itbase.h>
using itpp::vec;

NS_SVMACS_BEGIN

ZCR::ZCR(int samplerate) : Feature(samplerate, TEMPORAL) {}

ZCR::~ZCR() {}

const int INDEX = 0;

void ZCR::extract(const vec& frame, vec& features) const {
    const int len = frame.length();

    // get the sign
    vec sign = itpp::sign(frame);
    vec shft = itpp::concat(sign[0], sign.left(len - 1));

    // differentiate
    int cont = 0;
    int diff;
    for (int  i = 0; i < len; i++) {
        diff = sign[i] - shft[i];
        // count non-zero elements
        if (diff != 0) {
            cont++;
        }
    }

    double zcr = static_cast<double>(cont) / len * samplerate;
    features[INDEX] = zcr;
}

NS_SVMACS_END
