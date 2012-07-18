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

#ifndef SVMACS_MFCC_H
#define SVMACS_MFCC_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Mel-Frequency Cepstral Coefficients audio feature.
 */
class MFCC : public Feature {
public:
    MFCC(int samplerate, int nfft, int nfilters, int ncoeffs);
    ~MFCC();

    /// Compute the MFCC for the given spectrum frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;

private:

    /// Generate the Mel filter bank.
    void initFilterBank();

private:

    int nfft;     ///< Number of frequency bins.
    int nfilters; ///< Number of Mel filters.
    int ncoeffs;  ///< Number of coefficients.

    itpp::mat filterBank; ///< Mel filter bank
};

NS_SVMACS_END

#endif // SVMACS_MFCC_H
