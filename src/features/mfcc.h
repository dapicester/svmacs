/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef MFCC_H
#define MFCC_H

#include "feature.h"
using namespace features;

#include <itpp/itbase.h>
using namespace itpp;

namespace features {

/// Extract the Mel-Frequecy Cepstral Coefficients
class MFCC : public Feature {
    /// Mel filter bank
    const mat* filterBank;

    /// Number of computed MFCCs
    static const int N_MFCC = 6;

public:
    MFCC(int samplerate, string name = "MFCC");
    ~MFCC();
    
    Type getType() const;

    void setFilterBank(const mat* fb);

    /** 
     * Generate the Mel filter bank
     * \param Nfft the number of frequency bins
     * \param Fs the sampling rate
     * \param NFilters the number of Mel filters
     */
    static mat const* getMelFilters(const int& Nfft, const int& Fs, const int& Nfilters); 
    
    /** 
     * Compute the MFCC for the given spectrum
     * \param frame the audio spectrum
     */
     void extract(const vec& frame, vec& features) const;
};

}

#endif
