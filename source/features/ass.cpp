/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

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
