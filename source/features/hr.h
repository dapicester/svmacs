/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_HR_H
#define SVMACS_HR_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Harmonic Ratio audio feature.
 * TODO: definition
 */
class HR : public Feature {
public:
    HR(int samplerate);
    ~HR();

    /// Compute the HR for the given audio frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

NS_SVMACS_END

#endif // SVMACS_HR_H
