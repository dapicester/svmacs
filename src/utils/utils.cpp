/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "utils.h"

#include <itpp/itbase.h>
#include <iostream>

/** 
 * Return a mirrored copy of the input vector. 
 */
//inline 
itpp::vec flipud(const itpp::vec& input) {
    const int len = input.length(); 
    itpp::vec output(len);
    for (int i = 0, j = len - 1; i<len; i++, j--) {
        output(i) = input(j);
    }
    return output;
}

/**
 * Find indices of nonzero elements. 
 */
//inline 
itpp::ivec find(const itpp::vec& input) {
    const int len = input.length(); 
    itpp::ivec idx;
    for (int i = 0; i < len; i++) {
        if (input[i] != 0.0) {
            idx = concat(idx, i);
        }
    }
    return idx;
}

/** 
 * Return difference and approximate derivative. 
 */
//inline 
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
//inline 
itpp::ivec maxima(const itpp::vec& input) {
    itpp::vec updown = sign(diff(input));
    
    itpp::vec flags; 
    flags = concat(flags, static_cast<double>(updown[0] < 0));
    flags = concat(flags, to_vec(diff(updown) < 0));
    flags = concat(flags, static_cast<double>(updown[updown.length() - 1] > 0));
    return itpp::to_ivec(find(flags));
}

/** 
 * Create a linear vector. 
 */
//inline 
itpp::vec linvec(const int start, const int stop) {
    const int size = stop - start + 1;
    itpp::vec out(size);
    for (int i = 0, val = start; i < size; i++, val++)
         out[i] = val;
    return out;
}

/*
inline 
const std::string vec2str(const itpp::vec& input) {
    std::ostringstream os(std::ostringstream::out);
    os << input;
    return os.str();
}

inline 
const std::string mat2str(const itpp::mat& input) {
    std::ostringstream os(std::ostringstream::out);
    os << input;
    return os.str();
}
 */