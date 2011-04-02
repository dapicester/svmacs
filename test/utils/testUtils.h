#ifndef TESTUTILS_H
#define	TESTUTILS_H

#include <itpp/itbase.h>
#include <iostream>

/**
 * Print a message on standard output.
 */
void print(const std::string& msg);

/**
 * Print on standard output the content of a vector.
 */
void print(const std::string& name,
           const itpp::vec& input);

/**
 * Print on standard output the content of a matrix.
 */
void print(const std::string& name,
           const itpp::mat& input);

/**
 * Get a linear vector to be used as a time vector.
 * @param start the start value
 * @param end the end value
 * @param step step size
 */
itpp::vec getTime(const double& start,
                  const double& end,
                  const double& step = 1.0);

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
itpp::vec getSignal(const itpp::vec& time,
                    const double& frequency = 1.0,
                    const double& noise = 0.0);

/**
 * Get a test signal.
 * @return a vector representing a test signal
 */
itpp::vec getSignal(const double& frequency = 1.0,
                    const double& noise = 0.0);

/**
 * Test for arrays equality.
 */
bool equals(double a[], double b[], int length);

#endif	/* TESTUTILS_H */
