/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#define RLOG_COMPONENT "jackclient"
#include <rlog/rlog.h>

#include"jackclient.h"
#define MIN(x,y) ((x) < (y) ? (x) : (y))

// JackClient* JackClient::instance = 0;

// JackClient* JackClient::getInstance() {
//     rDebug("getting client instance");
//     if ( instance == 0 ) {
//         rDebug("instantiating ...");
//         // initial ports from constructor created here.
//         instance = new JackClient();  
//     }
//     return instance;        
// }

JackClient::JackClient() : JackCpp::AudioIO("svm-acs", NUM_INPUT, NUM_OUTPUT) {
    rDebug("constructor called");
}

JackClient::~JackClient() {
//     delete instance;
    rDebug("destructor called");
}

/** Jack Audio callback. */
int JackClient::audioCallback(jack_nframes_t nframes, 
                                      audioBufVector inBufs,
                                      audioBufVector outBufs) {
    for(unsigned int i = 0; i < MIN(inBufs.size(),outBufs.size()); i++) {
        // A simple example: copy the input to the output.
        for(unsigned int j = 0; j < nframes; j++) {
            outBufs[i][j] = inBufs[i][j];  
        }
    }
    //0 on success
    return 0;
}   
    
