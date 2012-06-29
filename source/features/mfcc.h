/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

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
