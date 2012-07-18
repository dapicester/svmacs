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

#ifndef SVMACS_SVMACCLI_H
#define SVMACS_SVMACCLI_H

#include "config.h"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>

NS_SVMACS_BEGIN

class Engine;

/**
 * CLI interface for the SVM Audio Classifier.
 */
class SvmacCli : private boost::noncopyable {
public:

    /// Constructor.
    SvmacCli();

    /// Destructor.
    ~SvmacCli();

    /**
     * Start the CLI.
     * @param length
     *          frame length (in seconds)
     * @param overlap
     *          frame overlapping ratio (percentage)
     * @param dmodel
     *          path to the detection model file
     * @param cmodel
     *          path to the classification model file
     */
    void start(const float length, const float overlap,
            const std::string& dmodel, const std::string& cmodel);

private:

    boost::scoped_ptr<Engine> engine; ///< The actual running audio engine.

    // TODO: signal handler (maybe boost::asio)
    static void cleanup(int); ///< Signal handler function.
    static bool flag;         ///< Running flag.
};

NS_SVMACS_END

#endif // SVMACS_SVMACCLI_H
