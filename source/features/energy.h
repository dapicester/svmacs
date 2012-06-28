/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_ENERGY_H
#define SVMACS_ENERGY_H

#include "feature.hpp"

NS_SVMACS_BEGIN

/**
 * Energy audio feature.
 * TODO: definition
 */
class Energy : public Feature {
public:
    Energy(int samplerate);
    ~Energy();

    /// Compute the energy for the given frame.
    void extract(const itpp::vec& frame, itpp::vec& features) const;
};

NS_SVMACS_END

#endif // SVMACS_ENERGY_H
