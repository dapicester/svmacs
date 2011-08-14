/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef SVMACS_CLI_H
#define SVMACS_CLI_H

class Engine;

/** 
 * @class SvmacCli
 * @brief CLI interface for the SVM Audio Classifier. 
 * @author Paolo D'Apice
 */
class SvmacCli {
public:
    SvmacCli();
    ~SvmacCli();

    /** 
     * Start the client. 
     * @param length
     *          frame length (in seconds)
     * @param overlap
     *          frame overlapping ratio (percentage)
     */
    void start(float length, float overlap);

private:
    /// pointer to the engine
    Engine* engine;
    
    /// signal handler
    static void cleanup(int);
    /// running flag
    static bool flag;
};

#endif // SVMACS_CLI_H
