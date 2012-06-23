/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "hr.h"
#include "utils/utils.h"

#include <itpp/itsignal.h>
using itpp::vec;
using itpp::ivec;

#define RLOG_COMPONENT "hr"
#include <rlog/rlog.h>

NS_SVMACS_BEGIN

HR::HR(int samplerate) : Feature(samplerate, TEMPORAL) {
    name = "HR";
}

HR::~HR() {
}

const int INDEX = 5;

void HR::extract(const vec& frame, vec* features) const {
    double hr = 0.0;

    if (numel(find(frame)) != 0) { // no silence
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

    (*features)[INDEX] = hr;
}

NS_SVMACS_END