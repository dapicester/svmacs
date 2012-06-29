/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

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
