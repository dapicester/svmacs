/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <itpp/itsignal.h>
#include <iostream>

namespace svmacs {

// TODO tutto da rivedere
// TODO usare out param invece che return
// TODO aggiungere inline

/**
 * Return a mirrored copy of the input vector.
 */
static 
itpp::vec flipud(const itpp::vec& input) {
    const int len = input.length();
    itpp::vec output(len);
    for (int i = 0, j = len - 1; i<len; i++, j--) {
        output(i) = input(j);
    }
    return output;
}

/**
 * Return the number of elements of a vector.
 */
template <typename T>
unsigned int numel(const itpp::Vec<T>& input) {
    return input.length();
}

/**
 * Find indices of nonzero elements.
 */
static 
itpp::ivec find(const itpp::vec& input) {
    const int len = input.length();
    itpp::ivec idx;
    for (int i = 0; i < len; i++) {
        if (input[i] != 0.0) {
            idx = itpp::concat(idx, i);
        }
    }
    return idx;
}

/**
 * Return difference and approximate derivative.
 */
static
itpp::vec diff(const itpp::vec& input) {
    const int len = input.length() - 1;
    itpp::vec out(len);
    for (int i = 0; i < len; i++)
        out[i] = input[i + 1] - input[i];
    return out;
}

/**
 * Find local maxima indices.
 */
static
itpp::ivec maxima(const itpp::vec& input) {
    itpp::vec updown = itpp::sign(diff(input));

    itpp::vec flags;
    flags = itpp::concat(flags, static_cast<double>(updown[0] < 0));
    flags = itpp::concat(flags, itpp::to_vec(diff(updown) < 0));
    flags = itpp::concat(flags, static_cast<double>(updown[updown.length() - 1] > 0));
    return itpp::to_ivec(find(flags));
}

/**
 * Create a linear vector.
 */
static 
itpp::vec linvec(const int start, const int stop) {
    const int size = stop - start + 1;
    itpp::vec out(size);
    for (int i = 0, val = start; i < size; i++, val++)
         out[i] = val;
    return out;
}

/**
 * Compute the spectrum of the given signal.
 */
inline itpp::vec 
getSpectrum(const itpp::vec& input, const int& nfft) {
    return itpp::abs( itpp::fft( itpp::to_cvec(input), nfft) ).left(nfft/2);
}

} /* namespace svmacs */

#endif // UTILS_H
