/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVM_UTILS_H
#define SVM_UTILS_H

#include <itpp/itbase.h>
using itpp::vec;
using itpp::ivec;
using itpp::to_ivec;
using itpp::mat;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostringstream;
using std::ios;

namespace utils {

/** Return a mirrored copy of the input vector. */
inline vec flipud(const vec& input) {
    const int len = input.length(); 
    vec output(len);
    for (int i=0, j=len-1; i<len; i++, j--) {
        output(i) = input(j);
    }
    
    return output;
}

/** Return the number of elements. */
inline uint numel(const vec& input) {
    return input.length();
}

/** Return the number of elements. */
inline uint numel(const ivec& input) {
    return input.length();
}

/** Find indices of nonzero elements. */
inline ivec find(const vec& input) {
    const int len = input.length(); 
    ivec idx;
    for (int i=0; i<len; i++) {
        if (input[i] != 0.0) {
            idx = concat(idx, i);
        }
    }
    return idx;
}

/** Return difference and approximate derivative. */
inline vec diff(const vec& input) {
    const int len = input.length()-1; 
    vec out(len);
    for (int i=0; i<len; i++)
        out[i] = input[i+1] - input[i];
    return out;
}

/** Find local maxima indices. */
inline ivec maxima(const vec& input) {
    vec updown = sign(diff(input));
    
    vec flags; 
    flags = concat(flags, static_cast<double>(updown[0] < 0));
    flags = concat(flags, to_vec(diff(updown) < 0));
    flags = concat(flags, static_cast<double>(updown[updown.length()-1] > 0));
    return to_ivec(find(flags));
}

} // namespace utils

namespace cli {

inline void pressKey () {
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();

    return;
}

inline const char* vec2str(const vec& input) {
    ostringstream os(ios::out);
    os << input;
    return os.str().c_str();
}

inline const char* mat2str(const mat& input) {
    ostringstream os(ios::out);
    os << input;
    return os.str().c_str();
}

} // namespace cli

#endif
