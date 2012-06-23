/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_CLI_H
#define SVMACS_CLI_H

#include "config.h"
#include <boost/noncopyable.hpp>
#include <string>

NS_SVMACS_BEGIN

class Engine;

/** 
 * @class SvmacCli
 * @brief CLI interface for the SVM Audio Classifier. 
 * @author Paolo D'Apice
 */
class SvmacCli : private boost::noncopyable {
public:
    SvmacCli();
    ~SvmacCli();

    /** 
     * Start the client. 
     * @param length
     *          frame length (in seconds)
     * @param overlap
     *          frame overlapping ratio (percentage)
     * @param dmodel
     *          path to the detection model file
     * @param cmodel
     *          path to the classification model file
     */
    void start(float length, float overlap, 
            const std::string& dmodel, const std::string& cmodel);

private:
    /// pointer to the engine
    Engine* engine; // TODO: boost::scoped_ptr
    
    /// signal handler
    static void cleanup(int); // TODO: signal handler (maybe boost::asio)
    /// running flag
    static bool flag;
};

NS_SVMACS_END

#endif // SVMACS_CLI_H
