/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <itpp/base/vec.h>

// TODO tutto da rivedere
// TODO aggiungere in coda #include "utils.cpp" per header-only

/** 
 * Return a mirrored copy of the input vector. 
 */
itpp::vec flipud(const itpp::vec& input);

/** 
 * Return the number of elements of a vector. 
 */
template <class T>
unsigned int numel(const itpp::Vec<T>& input) {
    return input.length();
}

/**
 * Find indices of nonzero elements. 
 */
itpp::ivec find(const itpp::vec& input);

/** 
 * Return difference and approximate derivative. 
 */
itpp::vec diff(const itpp::vec& input);

/** 
 * Find local maxima indices.
 */
itpp::ivec maxima(const itpp::vec& input);

/** 
 * Create a linear vector. 
 */
itpp::vec linvec(const int start, const int stop);

#endif // UTILS_H
