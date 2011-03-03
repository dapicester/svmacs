#ifndef TESTUTILS_H
#define	TESTUTILS_H

#include "utils/convert.h"
#include <itpp/itbase.h>

/**
 * Print on standard output the content of a vector. 
 */
void print(const itpp::vec& input);

/**
 * Get a linear vector to be used as a time vector.
 * @param start the start value
 * @param end the end value
 * @param step step size
 */
itpp::vec getTime(const double start, const double end, const double step);

/**
 * Get a silence signal.
 * @return a vector of zeros
 */
itpp::vec getSilence();

/**
 * Get a silence signal.
 * @param time the time vector
 * @return a vector of zeros
 */
itpp::vec getSilence(const itpp::vec& time);

/**
 * Get a test signal.
 * @param time the time vector
 * @return a vector representing a test signal
 */
itpp::vec getSignal(const itpp::vec& time);

/**
 * Get a test signal.
 * @return a vector representing a test signal
 */
itpp::vec getSignal();

#endif	/* TESTUTILS_H */

