/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_CLI_H
#define SVMACS_CLI_H

#include "../jack/jackclient.h"
using jack::JackClient;

namespace cli {

/** 
@class SvmacCli
@brief CLI interface for the SVM Audio Classifier. 
@author Paolo D'Apice
*/
class SvmacCli {
    /** Singleton instance. */
    static SvmacCli* instance;
    
    /** Private constructor. */
    SvmacCli(); 
        
    /** Signal handler function. */
    static void cleanup(int);

    /** Pointer to the Jack client. */
    JackClient* client;
    
public:
    /** Destructor. */
    ~SvmacCli();
    
    /**
     * Entry point. 
     * \return the singleton instance
     */
    static SvmacCli* getInstance();
    
    /** 
     * CLI main loop. 
     * \param N frame length in seconds
     * \param R percentage of frame overlap     
     */
    void mainLoop(float N, float R);
};

}

#endif // SVMACS_CLI_H
