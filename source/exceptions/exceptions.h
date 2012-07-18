/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef SVMACS_EXCEPTIONS_H
#define SVMACS_EXCEPTIONS_H

#include "config.h"
#include <stdexcept>

NS_SVMACS_BEGIN

/**
 * Runtime exception thrown on Jack errors.
 */
class JackException : public std::runtime_error {
public:
    JackException(const std::string& s = "") : std::runtime_error(s) { }
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
    BadConversion(const std::string& s = "") : std::runtime_error(s) { }
};

/**
 * Runtime exception for initialization errors.
 */
class NotInitialized : public std::runtime_error {
public:
    NotInitialized(const std::string& s = "") : std::runtime_error(s) { }
};

NS_SVMACS_END

#endif // SVMACS_EXCEPTIONS_H
