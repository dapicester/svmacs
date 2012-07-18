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
