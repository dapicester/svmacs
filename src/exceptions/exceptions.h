/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

#include <stdexcept>

/**
 * Runtime exception thrown on Jack errors.
 */
class JackException : public std::runtime_error {
public:
    JackException(const std::string& s = "") : std::runtime_error(s) {}
};

/** 
 * Runtime exception for model loading errors.
 */
class BadModel : public std::runtime_error {
public:
    BadModel(const std::string& s = "") : std::runtime_error(s) {}
};

/**
 * Runtime exception for string conversion errors.
 */
class BadConversion : public std::runtime_error {
public:
    BadConversion(const std::string& s = "") : std::runtime_error(s) {}
};

/**
 * Runtime exception for initialization errors.
 */
class NotInitialized : public std::runtime_error {
public:
    NotInitialized(const std::string& s = "") : std::exception(s) {}
};

#endif	/* EXCEPTIONS_H */
