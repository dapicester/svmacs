/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "energy.h"
#include "config.h"

#include <itpp/itbase.h>
using itpp::vec;

NS_SVMACS_BEGIN

Energy::Energy(int samplerate) : Feature(samplerate, TEMPORAL) {}

Energy::~Energy() {}

const int INDEX = 1;

void Energy::extract(const vec& frame, vec& features) const {
    const int len = frame.length();

    vec square = itpp::sqr(itpp::abs(frame));
    double energy = itpp::sum(square) / len * samplerate;

    features[INDEX] = energy;
}

NS_SVMACS_END
