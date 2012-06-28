/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_ZCR_H
#define SVMACS_ZCR_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Zero-Crossing-Rate audio feature.
 * TODO: definition
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
