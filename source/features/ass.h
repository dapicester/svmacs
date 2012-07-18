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

#ifndef SVMACS_ASS_H
#define SVMACS_ASS_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Audio Spectral Spread and Audio Spectral Centroid audio features.
 */
class ASS : public Feature {
public:
    ASS(int samplerate);
    ~ASS();

    /// Compute the ASS and the ASC for the given spectrum frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

NS_SVMACS_END

#endif // SVMACS_ASS_H
