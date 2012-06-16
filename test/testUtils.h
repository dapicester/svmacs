#ifndef TESTUTILS_H
#define	TESTUTILS_H

#include <itpp/itbase.h>
#include "boost/lexical_cast.hpp"
#include <iostream>

namespace test {

/**
 * Print a message on standard output.
 */
void 
print(const std::string& message) {
    std::cout << message << std::endl;
}

/**
 * Print on standard output the content of a vector.
 */
void
print(const std::string& name, const itpp::vec& input) {
    std::cout << "\n" << name << ": " << input << std::endl;
}

/**
 * Print on standard output the content of a matrix.
 */
void 
print(const std::string& name, const itpp::mat& input) {
    std::cout << "\n" << name << ": " << input << std::endl;
}

/**
 * Get a linear vector to be used as a time vector.
 * @param start the start value
 * @param end the end value
 * @param step step size
 */
itpp::vec 
getTime(double start, double end, double step = 1.0) {
    std::string s;
    if (step != 1.0) {
        s = boost::lexical_cast<std::string>(start)
          + ":" + boost::lexical_cast<std::string>(step)
          + ":" + boost::lexical_cast<std::string>(end) ;
    } else {
        s = boost::lexical_cast<std::string>(start)
          + ":" + boost::lexical_cast<std::string>(end) ;
    }

    itpp::vec out(s);
    return out;
}

/// Sample data length.
const int DEFAULT_LENGTH = 128;

/**
 * Get a silence signal.
 * @return a vector of zeros
 */
itpp::vec 
getSilence() {
    itpp::vec silence(DEFAULT_LENGTH);
    silence.zeros();
    return silence;
}

/**
 * Get a silence signal.
 * @param time the time vector
 * @return a vector of zeros
 */
itpp::vec 
getSilence(const itpp::vec& time) {
    itpp::vec silence(time.size());
    silence.zeros();
    return silence;
}

/**
 * Get a test signal.
 * @param time the time vector
 * @return a vector representing a test signal
 */
itpp::vec 
getSignal(const itpp::vec& time,
                    double frequency = 1.0,
                    double noise = 0.0) {
    return itpp::sin(itpp::m_2pi * frequency * time ) + sqrt(noise) * itpp::randn(time.length());
}

/**
 * Get a test signal.
 * @return a vector representing a test signal
 */
itpp::vec 
getSignal(const double& frequency = 1.0,
                    const double& noise = 0.0) {
    const itpp::vec time = getTime(0, DEFAULT_LENGTH);
    return getSignal(time, frequency, noise);
}

/**
 * Test for arrays equality.
 */
bool equals(double a[], double b[], int length) {
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

} /* namespace test */

#endif	/* TESTUTILS_H */
