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

#ifndef SVMACS_ZCR_H
#define SVMACS_ZCR_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Zero-Crossing-Rate audio feature.
 */
class ZCR : public Feature {
public:
    ZCR(int samplerate);
    ~ZCR();

    /// Compute the ZCR for the given frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

NS_SVMACS_END

#endif // SVMACS_ZCR_H
