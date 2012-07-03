#ifndef TEST_TESTUTILS_H
#define TEST_TESTUTILS_H

#include <itpp/itbase.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <sstream>

namespace test {

/// Print a message on standard output.
void print(const std::string& message) {
    std::cout << "> " << message << std::endl;
}

/// Print on standard output the content of a vector.
template <typename T>
void print(const std::string& name, const T& input) {
    std::cout << "> " << name << ":\n" << input << std::endl;
}

/**
 * Get a linear vector to be used as a time vector.
 * @param start the start value
 * @param end the end value
 * @param step step size
 * @return the time vector
 */
template <typename T>
itpp::Vec<T>
getTime(T start, T end, T step = static_cast<T>(1)) {
    std::stringstream ss;
    ss << boost::lexical_cast<std::string>(start);
    if (step != 1.0) {
        ss << ":" << boost::lexical_cast<std::string>(step);
    }
    ss << ":" + boost::lexical_cast<std::string>(end);

    return itpp::vec(ss.str());
}

/// Sample data length.
const size_t DEFAULT_LENGTH = 1024;

/**
 * Get a silence signal.
 * @param time the time vector
 * @return a vector of zeros
 */
itpp::vec
getSilence(size_t length = DEFAULT_LENGTH) {
    itpp::vec silence(length);
    silence.zeros();
    return silence;
}

/**
 * Get a test signal
 * \f$ s(t) = \sin{(2 \pi f t)} + \sqrt{n}\,\mathrm{randn}(t) \f$.
 * @param time the time vector \f$ t \f$
 * @param frequency the frequency \f$ f \f$
 * @param noise n the variance of the noise \f$ n \f$
 * @return the signal vector
 */
itpp::vec
getSignal(const itpp::vec& time, double frequency = 1.0, double noise = 0.0) {
    return itpp::sin(itpp::m_2pi * frequency * time )
        + sqrt(noise) * itpp::randn(time.length());
}

} /* namespace test */

#endif // TEST_TESTUTILS_H
