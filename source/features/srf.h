/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_SRF_H
#define SVMACS_SRF_H

#include"feature.hpp"

NS_SVMACS_BEGIN

/**
 * Spectral Roll-off audio feature.
 */
class SRF : public Feature {
public:
    SRF(int samplerate);
    ~SRF();

    /// Compute the SRF for the given spectrum frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

NS_SVMACS_END

#endif // SVMACS_SRF_H
