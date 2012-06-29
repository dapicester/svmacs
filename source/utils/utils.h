/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_UTILS_H
#define SVMACS_UTILS_H

#include "config.h"
#include <itpp/itsignal.h>
#include <iostream>
#include <cassert>

NS_SVMACS_BEGIN

// TODO usare out param invece che return

/**
 * Return a mirrored copy of the input vector.
 * Example:
 *  input  = "1 2 3"
 *  output = "3 2 1"
 * @param input a vector
 * @return a new vector
 */
template <typename T>
inline itpp::Vec<T>
flipud(const itpp::Vec<T>& input) {
    const int len = input.length();
    itpp::Vec<T> output(len);
    for (int i = 0, j = len - 1; i < len; i++, j--) {
        output(i) = input(j);
    }
    return output;
}

/**
 * Find indices of nonzero elements.
 * Example:
 *   input  = "1 0 2 3 0"
 *   output = "0 2 3"
 * @param input a vector
 * @return a new vector of integers
 */
template <typename T>
inline itpp::ivec
find(const itpp::Vec<T>& input) {
    const int len = input.length();
    itpp::ivec idx(len);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] != 0.0) {
            idx[j++] = i;
        }
    }
    return idx.left(j);
}

/**
 * Return difference and approximate derivative.
 * Example:
 *   input  = "2 4 3 5 5"
 *   output = "2 -1 2 0"
 * @param input a vector
 * @return a new vector
 */
template <typename T>
inline itpp::Vec<T>
diff(const itpp::Vec<T>& input) {
    const int len = input.length() - 1;
    itpp::Vec<T> out(len);
    for (int i = 0; i < len; i++) {
        out[i] = input[i + 1] - input[i];
    }
    return out;
}

/**
 * Find local maxima indices.
 * Example:
 *   input  = "2 3 4 1 2 0"
 *   output = "2 4"
 * @param input a vector
 * @return a new vector of integers
 */
template <typename T>
inline itpp::ivec
maxima(const itpp::Vec<T>& input) {
    itpp::Vec<T> updown = itpp::sign(diff(input));

    itpp::Vec<T> flags;
    flags = itpp::concat(flags, static_cast<T>(updown[0] < 0));
    flags = itpp::concat(flags, itpp::to_vec(diff(updown) < 0));
    flags = itpp::concat(flags, static_cast<T>(updown[updown.length() - 1] > 0));
    return find(flags);
}

/**
 * Create a linear vector.
 * @param start the initial value
 * @param stop the final value, it must hold that stop > start
 * @param step the step value
 * @return a new vector
 */
template <typename T>
inline itpp::Vec<T>
linvec(const T start, const T stop, const T step = static_cast<T>(1)) {
    assert(stop > start);
    const int size = stop - start + 1;
    itpp::Vec<T> out(size);
    T val = start;
    for (int i = 0; i < size; i++) {
        out[i] = val;
        val += step;
    }
    return out;
}

/**
 * Compute the spectrum of the given signal.
 * @param input a vector
 * @param nfft the number of frequency bins
 * @return a new vector
 */
inline itpp::vec
getSpectrum(const itpp::vec& input, int nfft) {
    return itpp::abs( itpp::fft( itpp::to_cvec(input), nfft) ).left(nfft/2);
}

NS_SVMACS_END

#endif // SVMACS_UTILS_H
