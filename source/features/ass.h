/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_ASS_H
#define SVMACS_ASS_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Audio Spectral Spread and Audio Spectral Centroid audio features.
 * TODO: definitions
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
