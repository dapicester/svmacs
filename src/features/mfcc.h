/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef MFCC_H
#define MFCC_H

#include <features/feature.h>

#include <itpp/itbase.h>
using itpp::mat;

namespace features {

/**
 * Mel-Frequecy Cepstral Coefficients audio feature.
 * TODO: definition
 */
class MFCC : public Feature {
  
  public:
    
    MFCC(int samplerate, int nfft, int nfilters);
    
    ~MFCC();
    
    /// Compute the MFCC for the given spectrum frame
    void extract(const vec& frame, vec& features) const;
      
  private:

    /// Number of frequency bins.
    int nfft;
    
    /// Number of Mel filters
    int nfilters;
    
    /// Mel filter bank
    const mat* filterBank;

    /// Number of computed MFCCs
    static const int N_MFCC = 6;
    
    /// Generate the Mel filter bank
    mat const* initFilterBank();
    
};

}

#endif
