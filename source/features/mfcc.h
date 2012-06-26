/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef MFCC_H
#define MFCC_H

#include "feature.h"

NS_SVMACS_BEGIN

/**
 * Mel-Frequency Cepstral Coefficients audio feature.
 * TODO: definition
 */
class MFCC : public Feature {
public:
    MFCC(int samplerate, int nfft, int nfilters, int ncoeffs);
    ~MFCC();

    /// Compute the MFCC for the given spectrum frame
    void extract(const itpp::vec& frame, itpp::vec* features) const;

    itpp::mat getFilterBank() const {
        return filterBank;
    }

private:
    /// Number of frequency bins.
    int nfft;

    /// Number of Mel filters
    int nfilters;

    /// Number of coefficients;
    int ncoeffs;

    /// Mel filter bank
    itpp::mat filterBank;

    /// Generate the Mel filter bank
    void initFilterBank();
};

NS_SVMACS_END

#endif
