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

#include "hr.h"
#include "utils/utils.h"

#include <itpp/itsignal.h>
using itpp::vec;
using itpp::ivec;

NS_SVMACS_BEGIN

HR::HR(int samplerate) : Feature(samplerate, TEMPORAL) {}

HR::~HR() {}

const int INDEX = 5;

void HR::extract(const vec& frame, vec& features) const {
    double hr = 0.0;

    if (find(frame).length() > 0) { // no silence
        // cross-correlation
        vec R = itpp::xcorr(frame, -1, "coeff");
        // discard first half
        const int rlen = R.length();
        R = R.right(itpp::ceil_i(rlen/2));
        // find peaks
        ivec idx = maxima(R);
        vec maxval = R(idx);

        int mlen = maxval.length();
        if(mlen != 1) { // more than one peek
            hr = itpp::max(maxval.right(mlen - 1));
        }
    }

    features[INDEX] = hr;
}

NS_SVMACS_END
